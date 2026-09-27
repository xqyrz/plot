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
    bool         checkable = false;
    bool         checked   = false;
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

    QModelIndex parent(const QModelIndex&) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
    AxfNode* nodeForIndex(const QModelIndex& index) const;
    void clearNodes();
    void rebuild();

    DwarfApp*    m_data;
    AxfNode*     m_root;
    QStringList  _header;
};

#endif //AXF_PLOTMODEL_H
