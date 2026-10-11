//
// Created by x on 2025/9/24.
//

#ifndef _AXFMODEL_H
#define _AXFMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include <QStringList>

class DwarfApp;

// 树节点类型：文件分组 / 变量 / 结构体成员（数组元素）
enum class AxfNodeType {
    FileGroup,  // 顶层：按源文件分组
    Variable,   // 变量行
    Member,     // 结构体/联合体成员 或 数组元素
};

struct AxfNode
{
    AxfNodeType  type = AxfNodeType::Variable;
    QString      name;      // Name 列
    QString      typeName;  // Type 列
    qulonglong   size = 0;      // Size 列
    qulonglong   address = 0;   // Address 列
    bool         checkable = false; //delete
    bool         checked   = false;
    bool         visible   = true;  // 过滤后是否可见（由 applyFilter 计算）
    AxfNode*     parent = nullptr;
    QVector<AxfNode*> children;
};

class AxfModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit AxfModel(QObject* parent = nullptr);
    ~AxfModel();

    // 加载指定 AXF 文件并重建模型
    void setFile(const QString& path);

    // 设置过滤文本：只显示 Name 或 Type 包含该文本（不区分大小写）的节点，
    // 以及它们的祖先节点。传空串清除过滤。
    void setFilterText(const  QList<QString>& text);
    QList<QString> filterText() const { return m_filterTexts; }

    QModelIndex parent(const QModelIndex&) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    void addNode(AxfNode* node);
private:
    AxfNode* nodeForIndex(const QModelIndex& index) const;
    void clearNodes();
    void rebuild();

    // 递归计算 visible：节点自身或任一后代匹配 m_filterText 则可见
    void applyFilter();
    bool nodeMatches(AxfNode* node) const;
    // 可见子节点列表（rowCount/index 用）
    QVector<AxfNode*> visibleChildren(AxfNode* parent) const;

    DwarfApp*    m_data;
    AxfNode*     m_root;
    QStringList  _header;
    QList<QString>      m_filterTexts;   // 过滤文本（空=不过滤）
};

#endif //AXF_PLOTMODEL_H
