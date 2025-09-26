//
// Created by x on 2025/9/24.
//

#ifndef PLOT_PLOTMODEL_H
#define PLOT_PLOTMODEL_H
#include <QAbstractTableModel>
#include <QPointer>
#include "plotdata.h"

class PlotModel: public QAbstractTableModel {
    Q_OBJECT
    typedef struct {
        QString arryName;
        QList<PlotData*> items;
        QString data(int col) {
            switch (col) {
                case 0:return "";
                case 1: return arryName;
                case 2: return "-1";
                    default:return "NAN";

            }
        }
    }_Node;
public:
    explicit PlotModel(QObject* parent = nullptr);
    ~PlotModel(){delete _root;};

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
private:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
signals:
        void chekStatusChanged(QSharedPointer<PlotData>& data);
public slots:
    void add_plotData(QSharedPointer<QCPGraphDataContainer> data, QString plot_name = "plot");

private:
    const QStringList _header = {"","名称","数据"};
    QList<_Node*>* _root{nullptr};
};


#endif //PLOT_PLOTMODEL_H