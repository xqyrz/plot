//
// Created by x on 2025/9/24.

#include "plotmodel.h"
#include "plotcommon.h"
/**
 *
 * @param parent
 */
PlotModel::PlotModel(QObject* parent)
    : QAbstractItemModel (parent)
{
    m_rootNode = new TreeNode(TreeNode::RootNode, "root");
    m_rootNode->append(new TreeNode(TreeNode::GroupNode, "组1"));
}


TreeNode* PlotModel::add_plotData(const uint64_t id,QSharedPointer<QCPGraphDataContainer>& data, QString plot_name ) {
    for (auto const& var : *m_rootNode) {
        for(auto const& var2 : *var) {
            if(var2->plotData->getData() == data) {
                qWarning() << "has data:"<<var2->name<<var2->plotData->getData();
                return nullptr;
            }
        }
    }
    int newRow = m_rootNode->at(0)->childCount();
    //TODO:第一次  warn:Invalid index ( 1 , 0 ) in model PlotModel(0x19d0fc8d6c0)
   // if (newRow)beginInsertRows(QModelIndex(), newRow, newRow);
    auto plotData = new PlotData(id,data,QColor(PLOT::color[size()%16]),plot_name,"",this);
    auto node = new TreeNode(plotData,plot_name);
    m_rootNode->at(0)->append(node);
   // if (newRow)endInsertRows(); // 通知视图：插入结束
    qDebug() << "PlotModel add "<<QString::number(id, 16) <<plot_name;
    return node;
}


QModelIndex PlotModel::parent(const QModelIndex & child) const {
    if (!child.isValid()) {
        return QModelIndex();  // 根节点没有父节点
    }

    // 获取子节点对应的 TreeNode
    TreeNode* childNode = static_cast<TreeNode*>(child.internalPointer());
    if (!childNode) {
        return QModelIndex();  // 安全保护
    }

    // 获取父节点
    auto parentNode = childNode->parent();
    if (!parentNode) {
        return QModelIndex();  // 没有父节点（应该是根节点）
    }

    // 如果父节点是根节点，返回无效索引
    if (parentNode == m_rootNode) {
        return QModelIndex();
    }

    // 找到父节点在其父级中的行号
    auto grandParent = parentNode->parent();
    if (!grandParent) {
        return QModelIndex();  // 安全保护
    }

    // 查找父节点在祖父节点子列表中的行号
    int row = grandParent->getChildren().indexOf(parentNode);
    if (row == -1) {
        return QModelIndex();  // 未找到，返回无效索引
    }

    // 创建父节点的索引
    return createIndex(row, 0, parentNode);
}

QModelIndex PlotModel::index(int row, int column, const QModelIndex &parent) const {
        if (!hasIndex(row, column, parent))return QModelIndex();

        if (!parent.isValid()) {//判断是不是顶层节点
            return  createIndex(row, column,m_rootNode->at(row));
        }

        auto parentItem =static_cast<TreeNode*>(parent.internalPointer());
        return  createIndex(row, column, parentItem->at(row));

}

int PlotModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return m_rootNode->childCount();
    }
    auto parentItem =static_cast<TreeNode*>(parent.internalPointer());
    if (parentItem) {
        return parentItem->childCount();
    }
       return 0;


}

int PlotModel::columnCount(const QModelIndex& parent) const
{
    return _header.count();
}

QVariant PlotModel::data(const QModelIndex& index, int role) const
{
    auto item = static_cast<TreeNode*>(index.internalPointer());
    if (!item) {
        return QVariant();
    }

    switch (role) {
        case Qt::DisplayRole:
            if (!index.parent().isValid()) {
                if (index.column()!=1) {
                    return QVariant();
                }
                return item->name;
            }
           switch (index.column()) {
            case 0:return QVariant();
            case 1:return item->plotData->getName();
            case 2:return  item->plotData->getShowData();
            default:QVariant();
           }
        case Qt::CheckStateRole: {
                if (index.column())return QVariant();
                if (item->type == TreeNode::PlotNode) {
                    return item->plotData->isVisible() ? Qt::Checked : Qt::Unchecked;
                }
                else if (item->type == TreeNode::GroupNode) {
                    for (auto const& var : *item) {
                        if (var->plotData->isVisible()) {
                            return Qt::Checked;
                        }
                    }
                    return Qt::Unchecked;
                }
            }
            return Qt::Checked;
        case   Qt::DecorationRole:      //NONE:X_这里可以优化
        {
            if (!index.parent().isValid()) return QVariant();
            if (index.column())return QVariant();
            QPixmap pixmap(32, 32);
            // 使用QPainter在QPixmap上绘制
            QPainter painter(&pixmap);
            // 绘制一个纯色背景
            painter.fillRect(pixmap.rect(),item->plotData->getColor());//_rootItems->data().at(index.row())->getcolor()); // 使用红色填充
            painter.setPen(QPen(Qt::black, 2)); // 设置画笔为黑色，宽度为2
            painter.drawRect(pixmap.rect().adjusted(1, 1, -1, -1)); // 绘制边框，稍微小于图标边界

            painter.end(); // 结束绘制
            return QIcon(pixmap);
        }
        case Qt::DecorationPropertyRole:return Qt::AlignCenter;
        case Qt::TextAlignmentRole: {
            Qt::Alignment align = Qt::AlignLeft | Qt::AlignVCenter;
            return QVariant(align);
        }
            default:return QVariant();
    }

}

QVariant PlotModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return _header[section];
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}


bool PlotModel::setData(const QModelIndex& _index, const QVariant& value, int role)
{
    switch (role) {
        case Qt::CheckStateRole: {
            if (_index.column() == 0) {
               auto item = static_cast<TreeNode*>(_index.internalPointer());
                switch (item->type) {
                case TreeNode::PlotNode:
                        item->plotData->setVisible(static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked);
                        emit dataChanged(_index, _index, {Qt::CheckStateRole});
                    break;
                case TreeNode::GroupNode: {
                    int row = 0;
                    for (auto const& var : *item) {
                        var->plotData->setVisible(static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked);
                        emit dataChanged(index(row,0,_index), index(row,0,_index), {Qt::CheckStateRole});
                        row++;
                    }
                    emit dataChanged(_index, _index, {Qt::CheckStateRole});
                    }
                    break;
                        default:break;
                }

            }
        }
        return true;
        default: return QAbstractItemModel::setData(_index, value, role);
    }
}

Qt::ItemFlags PlotModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.column() == 0)
        flags |= Qt::ItemIsUserCheckable;
    return flags;
}

int PlotModel::size() {
    int cnt =0;
    for (auto const& group : *m_rootNode) {
        cnt += group->childCount();
    }
    return cnt;
}

const TreeNode* PlotModel::getPlot(  QSharedPointer<QCPGraphDataContainer> ptr)
{
    TreeNode* plot=nullptr;
    for (auto const& group : *m_rootNode) {
        for (auto const& p : *group) {
           if (p->plotData->getData().data() == ptr.data())
           {
               return p;
           }
        }
    }
    return plot;
}

 TreeNode * PlotModel::getNode(uint64_t id) const {
    TreeNode* plot=nullptr;
    for (auto const& group : *m_rootNode) {
        for (auto const& p : *group) {
            if (p->plotData->getId() == id)
            {
                return p;
            }
        }
    }
    return plot;
}


