//
// Created by 25137 on 2026/9/27.
//

#include "axfmodel.h"
#include "dwarfapp.h"
#include <QDebug>
#include <QFont>
#include <QColor>
#include <functional>

AxfModel::AxfModel(QObject* parent)
    : QAbstractItemModel(parent)
    , m_data(new DwarfApp())
    , m_root(new AxfNode())
    , _header({"Name", "Type", "Size", "Address", "Select"})
{
}

AxfModel::~AxfModel()
{
    clearNodes();
    delete m_root;
    delete m_data;
}

void AxfModel::clearNodes()
{
    std::function<void(AxfNode*)> rec = [&](AxfNode* n) {
        for (AxfNode* c : n->children) {
            rec(c);
        }
        n->children.clear();
        delete n;
    };
    for (AxfNode* c : m_root->children) {
        rec(c);
    }
    m_root->children.clear();
}

void AxfModel::setFile(const QString& path)
{
    m_data->setFilePath(path.toStdString());
    try {
        m_data->loadFile();
    } catch (const std::exception& e) {
        qWarning() << "Failed to load DWARF file:" << e.what();
    }
    rebuild();
}

// 递归把结构体/联合体成员建成树节点（累积偏移 = 父基址 + 嵌套 offset）
static void buildMemberNodes(AxfNode* parentNode,
                             const std::vector<VarMemberInfo>& members,
                             uint64_t baseAddr)
{
    for (const auto& m : members) {
        AxfNode* mNode = new AxfNode();
        mNode->type     = AxfNodeType::Member;
        mNode->name     = QString::fromStdString(m.name);
        mNode->typeName = m.isStructOrUnion
                          ? "struct " + QString::fromStdString(m.type)
                          : QString::fromStdString(m.type);
        mNode->size     = m.size;
        mNode->address  = baseAddr + m.offset;
        mNode->parent   = parentNode;
        parentNode->children.append(mNode);

        // 该成员本身又是结构体/联合体：继续递归展开其子成员
        if (m.isStructOrUnion && !m.children.empty()) {
            buildMemberNodes(mNode, m.children, baseAddr + m.offset);
        }
    }
}

void AxfModel::rebuild()
{
    beginResetModel();
    clearNodes();

    const auto& vars = m_data->globalVariables();

    // 按文件路径分组，保持源文件顺序
    QVector<QString> order;
    struct FileSlot {
        AxfNode* node;
    };
    QMap<QString, FileSlot> fileNodes;

    for (const auto& v : vars) {
        QString file = QString::fromStdString(v.filePath);
        if (file.isEmpty()) {
            file = "(unknown)";
        }
        if (!fileNodes.contains(file)) {
            AxfNode* g = new AxfNode();
            g->type = AxfNodeType::FileGroup;
            g->name = file;
            g->parent = m_root;
            m_root->children.append(g);
            fileNodes.insert(file, FileSlot{ g });
            order.append(file);
        }
    }

    for (const auto& v : vars) {
        QString file = QString::fromStdString(v.filePath);
        if (file.isEmpty()) {
            file = "(unknown)";
        }
        AxfNode* g = fileNodes[file].node;

        AxfNode* varNode = new AxfNode();
        varNode->type      = AxfNodeType::Variable;
        varNode->name      = QString::fromStdString(v.name);
        varNode->typeName  = QString::fromStdString(v.type);
        varNode->size      = v.size;
        varNode->address   = v.address;
        varNode->checkable = true;
        varNode->parent    = g;
        g->children.append(varNode);

        // 结构体/联合体成员（递归展开到基本类型，如 MC→Foc→Uq/Ud）
        buildMemberNodes(varNode, v.members, v.address);

        // 数组元素
        if (v.isArray && v.arrayCount > 0) {
            uint64_t elemSize = (v.arrayCount > 0) ? (v.size / v.arrayCount) : 0;
            for (uint64_t i = 0; i < v.arrayCount; ++i) {
                AxfNode* eNode = new AxfNode();
                eNode->type     = AxfNodeType::Member;
                eNode->name     = QString("%1[%2]").arg(QString::fromStdString(v.name)).arg(i);
                eNode->typeName = QString::fromStdString(v.type);
                eNode->size     = elemSize;
                eNode->address  = v.address + i * elemSize;
                eNode->parent   = varNode;
                varNode->children.append(eNode);
            }
        }
    }

    Q_UNUSED(order);
    endResetModel();
}

AxfNode* AxfModel::nodeForIndex(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return m_root;
    }
    return static_cast<AxfNode*>(index.internalPointer());
}

QModelIndex AxfModel::parent(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return {};
    }
    AxfNode* node = nodeForIndex(index);
    AxfNode* p = node->parent;
    if (!p || p == m_root) {
        return {};
    }
    int row = 0;
    if (p->parent) {
        row = p->parent->children.indexOf(p);
    }
    return createIndex(row, 0, p);
}

QModelIndex AxfModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) {
        return {};
    }
    AxfNode* p = nodeForIndex(parent);
    if (row < 0 || row >= p->children.size()) {
        return {};
    }
    return createIndex(row, column, p->children[row]);
}

int AxfModel::rowCount(const QModelIndex& parent) const
{
    AxfNode* node = nodeForIndex(parent);
    return node ? node->children.size() : 0;
}

int AxfModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return _header.count();
}

QVariant AxfModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return {};
    }
    AxfNode* node = nodeForIndex(index);
    if (!node) {
        return {};
    }
    int col = index.column();

    if (role == Qt::DisplayRole) {
        switch (col) {
            case 0: return node->name;
            case 1: return node->typeName;
            case 2: return node->size ? QString::number(node->size) : QString();
            case 3: return node->address ? QString("0x%1").arg(node->address, 0, 16) : QString();
            case 4: return QString();
        }
    } else if (role == Qt::CheckStateRole) {
        if (col == 4 && node->checkable) {
            return node->checked ? Qt::Checked : Qt::Unchecked;
        }
    } else if (role == Qt::TextAlignmentRole) {
        if (col == 2 || col == 3) {
            return int(Qt::AlignRight | Qt::AlignVCenter);
        }
    } else if (role == Qt::FontRole) {
        if (node->type == AxfNodeType::FileGroup) {
            QFont f;
            f.setBold(true);
            return f;
        }
    } else if (role == Qt::ForegroundRole) {
        if (node->type == AxfNodeType::FileGroup) {
            return QColor(Qt::darkBlue);
        }
    }
    return {};
}

QVariant AxfModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return _header.value(section);
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

Qt::ItemFlags AxfModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    Qt::ItemFlags f = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    AxfNode* node = nodeForIndex(index);
    if (node && node->checkable && index.column() == 4) {
        f |= Qt::ItemIsUserCheckable;
    }
    return f;
}

bool AxfModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid()) {
        return false;
    }
    AxfNode* node = nodeForIndex(index);
    if (!node) {
        return false;
    }
    if (role == Qt::CheckStateRole && index.column() == 4 && node->checkable) {
        node->checked = (value.toInt() == Qt::Checked);
        emit dataChanged(index, index, { Qt::CheckStateRole });
        return true;
    }
    return QAbstractItemModel::setData(index, value, role);
}
