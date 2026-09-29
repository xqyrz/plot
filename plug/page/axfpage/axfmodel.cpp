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
        mNode->typeName = QString::fromStdString(m.type);
        mNode->size     = m.size;
        mNode->address  = baseAddr + m.offset;
        mNode->parent   = parentNode;
        parentNode->children.append(mNode);

        // 该成员本身是结构体/联合体 或 数组：继续递归展开其子成员
        if ((m.isStructOrUnion || m.isArray) && !m.children.empty()) {
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
        varNode->typeName  = (v.isStatic ? "static " : QString())+ QString::fromStdString(v.type);
        varNode->size      = v.size;
        varNode->address   = v.address;
        varNode->checkable = false;
        varNode->parent    = g;
        g->children.append(varNode);

        // 结构体/联合体成员（递归展开到基本类型，如 MC→Foc→Uq/Ud）
        buildMemberNodes(varNode, v.members, v.address);

        // 数组元素：子节点显示元素类型（去掉末尾的 [n] 维度）
        if (v.isArray && v.arrayCount > 0) {
            uint64_t elemSize = (v.arrayCount > 0) ? (v.size / v.arrayCount) : 0;
            QString arrType = QString::fromStdString(v.type);
            // 去掉末尾所有 [N] 维度，得到元素类型
            QString elemType = arrType;
            while (elemType.endsWith(']')) {
                int bracket = elemType.lastIndexOf('[');
                if (bracket < 0) break;
                elemType = elemType.left(bracket).trimmed();
            }
            for (uint64_t i = 0; i < v.arrayCount; ++i) {
                AxfNode* eNode = new AxfNode();
                eNode->type     = AxfNodeType::Member;
                eNode->name     = QString("%1[%2]").arg(QString::fromStdString(v.name)).arg(i);
                eNode->typeName = elemType;
                eNode->size     = elemSize;
                eNode->address  = v.address + i * elemSize;
                eNode->parent   = varNode;
                varNode->children.append(eNode);
                // 数组元素是结构体时，递归展开其成员（如 tfont32[0]→FNT成员）
                if (!v.members.empty()) {
                    buildMemberNodes(eNode, v.members, v.address + i * elemSize);
                }
            }
        }
    }

    Q_UNUSED(order);
    applyFilter();
    endResetModel();
}

// ===== 过滤 =====

bool AxfModel::nodeMatches(AxfNode* node) const
{
    if (m_filterTexts.isEmpty()) {
        return true;
    }

    QString str;
    // 匹配 Name 或 Type（不区分大小写）
    bool flag = true;
    for (auto & var:m_filterTexts)
    {
        if (var.isEmpty())continue;
        flag = false;
        if (node->name.contains(var, Qt::CaseInsensitive)
        || node->typeName.contains(var, Qt::CaseInsensitive))
        {
            return true;
        }
        for (auto& child:node->children)
        {
            if (child->name.contains(var, Qt::CaseInsensitive)
            || child->typeName.contains(var, Qt::CaseInsensitive))
            {
                return true;
            }
        }
        auto parent = node->parent;
        while (parent)
        {
           if (parent->name.contains(var, Qt::CaseInsensitive)
           || parent->typeName.contains(var, Qt::CaseInsensitive))
           {
               return true;
           }
            parent = parent->parent;
        }
    }

    return flag;
}

QVector<AxfNode*> AxfModel::visibleChildren(AxfNode* parent) const
{
    QVector<AxfNode*> out;
    if (!parent) return out;
    for (AxfNode* c : parent->children) {
        if (c->visible && nodeMatches(c)) {
            out.append(c);
        }
    }
    return out;
}

void AxfModel::applyFilter()
{
    // 自底向上计算 visible：节点自身匹配 或 任一后代匹配
    std::function<bool(AxfNode*)> rec = [&](AxfNode* n) -> bool {
        bool selfMatch = nodeMatches(n);
        bool childMatch = false;
        for (AxfNode* c : n->children) {
            if (rec(c)) {
                childMatch = true;
            }
        }
        n->visible = selfMatch || childMatch;
        return n->visible;
    };
    rec(m_root);
}

void AxfModel::setFilterText(const  QList<QString>& text)
{
    beginResetModel();
    m_filterTexts = text;
    applyFilter();
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
    // 计算在可见兄弟中的行号
    int row = 0;
    if (p->parent) {
        int idx = 0;
        for (AxfNode* c : p->parent->children) {
            if (c == p) break;
            if (c->visible) ++idx;
        }
        row = idx;
    }
    return createIndex(row, 0, p);
}

QModelIndex AxfModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) {
        return {};
    }
    AxfNode* p = nodeForIndex(parent);
    QVector<AxfNode*> vc = visibleChildren(p);
    if (row < 0 || row >= vc.size()) {
        return {};
    }
    return createIndex(row, column, vc[row]);
}

int AxfModel::rowCount(const QModelIndex& parent) const
{
    AxfNode* node = nodeForIndex(parent);
    if (!node) return 0;

    return visibleChildren(node).size();
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
            case 0:
              if (node->type == AxfNodeType::FileGroup)
              {
                  return node->name.split('/').last().split('\\').last();
              }
            else
            {
                return node->name;
            }
            case 1: return node->typeName;
            case 2: return node->size ? QString::number(node->size) : QString();
            case 3: return node->address ? QString("0x%1").arg(node->address, 0, 16) : QString();
            case 4: return QString();
        }
    } else if (role == Qt::CheckStateRole) {
    // if (col == 4 && node->checkable) {
        if (col == 4 && (node->children.size() ==0) && (node->type != AxfNodeType::FileGroup) ) {
         return node->checked ? Qt::Checked : Qt::Unchecked;
     }
    } else if (role == Qt::TextAlignmentRole) {
        //if (col == 2 || col == 3) {
            return int(Qt::AlignLeft | Qt::AlignVCenter);
      // }
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
