//
// Created by x on 2025/9/24.
//

#ifndef PLOT_PLOTMODEL_H
#define PLOT_PLOTMODEL_H
#include <QAbstractItemModel>
#include <QPointer>
#include "qcustomplot/qcustomplot.h"
#include "plotdata.h"
class TreeNode {
public:
    enum NodeType {
        RootNode,      // 根节点
        GroupNode,     // 曲线组节点
        PlotNode       // 曲线数据节点
    };

    NodeType type;
    const QString name;


     PlotData* const plotData = nullptr;  // 只有PlotNode类型才有数据

    TreeNode(NodeType t, const QString& n = "") : type(t), name(n) {}
    TreeNode(PlotData* p, const QString& n) :type(PlotNode), name(n), plotData(p) {}
    ~TreeNode() {
        qDeleteAll(children);
        delete plotData;
    }
    void append(TreeNode* node) {
       node->setparent(this);
        children.append(node);
    }
     TreeNode* const at(int i) const{
        if (i >= 0 && i < children.size())
            return children.at(i);
        return nullptr;
    }
    int childCount() const { return children.size(); }

    QList<TreeNode*>::iterator begin() { return children.begin(); }
    QList<TreeNode*>::iterator end() { return children.end(); }
    QList<TreeNode*>::const_iterator begin() const { return children.begin(); }
    QList<TreeNode*>::const_iterator end() const { return children.end(); }

     TreeNode* parent() const { return _parent; }
    QList<TreeNode*> getChildren() const { return children; }
private:
    QList<TreeNode*> children;
     TreeNode* _parent = nullptr;
    void setparent( TreeNode* p) { _parent = p; }
};
class PlotModel: public QAbstractItemModel  {
    Q_OBJECT
public:
    explicit PlotModel(QObject* parent = nullptr);
    ~PlotModel(){delete m_rootNode;};

    QModelIndex parent(const QModelIndex&) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
     TreeNode*  root() const { return m_rootNode; }
    const TreeNode* getPlot(  QSharedPointer<QCPGraphDataContainer>);
private:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    int size();

signals:
        void chekStatusChanged(QSharedPointer<PlotData>& data);
public slots:
    void add_plotData(const uint64_t id, QSharedPointer<QCPGraphDataContainer>& data, QString plot_name = "plot");

private:
    const QStringList _header = {"","名称","数据"};
    TreeNode* m_rootNode;
};


#endif //PLOT_PLOTMODEL_H