//
// Created by x on 2025/9/24.

#include "plotmodel.h"

/**
 *
 * @param parent
 */
PlotModel::PlotModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    _root = new QList<_Node *>();
    _root->append(new _Node{""});
}

/// <summary>
/// 显示曲线数据
/// </summary>
/// <param name="data">数据</param>
/// <param name="plot_name">label</param>
void PlotModel::add_plotData(QSharedPointer<QCPGraphDataContainer> data, QString plot_name ) {
    for (auto const& var : *_root) {
        for(auto const& var2 : var->items) {
            if(var2->getData() == data) {
                qWarning() << "has data:"<<var2->getName()<<var2->getData();
            }
        }
    }
    int newRow = _root->at(0)->items.size();

    beginInsertRows(QModelIndex(), newRow, newRow);
    _root->at(0)->items.append(new PlotData(data,plot_name,"",this));
    endInsertRows(); // 通知视图：插入结束
}


QModelIndex PlotModel::index(int row, int column, const QModelIndex &parent) const {
        if (!hasIndex(row, column, parent))return QModelIndex();
        if (parent.isValid()) {
            auto parentItem =static_cast<_Node*>(parent.internalPointer());
            return  createIndex(row, column, parentItem->items.at(row));
        }
        else {
            return  createIndex(row, column, _root->at(row));
        }

}

int PlotModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return static_cast<_Node*>(parent.internalPointer())->items.size();
    }
    else {
        return _root->size();
    }
}

int PlotModel::columnCount(const QModelIndex& parent) const
{
    return _header.count();
}

QVariant PlotModel::data(const QModelIndex& index, int role) const
{
   auto node = static_cast<_Node*>(index.internalPointer());
    if (node) return node->arryName;

    auto item = static_cast<PlotData*>(index.internalPointer());
    if (!item)return QVariant();

    switch (role) {
        case Qt::DisplayRole:
           switch (index.column()) {
            case 0:return QVariant();
            case 1:return item->getName();
            case 2:return  item->getShowData();
            default:QVariant();
           }
        case Qt::CheckStateRole:
            return Qt::Checked;
        case   Qt::DecorationRole:      //TODO:X_这里一定要优化
        {
            if (index.column())return QVariant();
            QPixmap pixmap(32, 32);
            // 使用QPainter在QPixmap上绘制
            QPainter painter(&pixmap);
            // 绘制一个纯色背景
            painter.fillRect(pixmap.rect(), Qt::red);//_rootItems->data().at(index.row())->getcolor()); // 使用红色填充
            painter.setPen(QPen(Qt::black, 2)); // 设置画笔为黑色，宽度为2
            painter.drawRect(pixmap.rect().adjusted(1, 1, -1, -1)); // 绘制边框，稍微小于图标边界

            painter.end(); // 结束绘制
            return QIcon(pixmap);
        }
        case Qt::DecorationPropertyRole:return Qt::AlignCenter;
        case Qt::TextAlignmentRole:return Qt::AlignCenter;
            default:return QVariant();
    }

}

QVariant PlotModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return _header[section];
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

bool PlotModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::CheckStateRole) {
        // 更新项的选中状态
   //      if (_rootItems->data().at(index.row())->getcheckStatus() != value.toBool()) {
			// _rootItems->data()[index.row()]->setcheckStatus(value.toBool());
   //     }
        return true;
    }
    return QAbstractTableModel::setData(index, value, role);
}

Qt::ItemFlags PlotModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == 0)
        flags |= Qt::ItemIsUserCheckable;
    return flags;
}
