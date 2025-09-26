//
// Created by x on 2025/9/24.
//

#ifndef PLOT_PLOTDATA_H
#define PLOT_PLOTDATA_H

#include <QObject>
#include "./qcustomplot/qcustomplot.h"
class PlotData: public QObject {
    Q_OBJECT
public:
    explicit PlotData(QSharedPointer<QCPGraphDataContainer> data,const QString &name, const QString &units, QObject *parent = nullptr);
    ~PlotData() override = default;

    QString getName() const{return name;};
    QString getUnits() const{return units;};
    QString getShowData()const;
    QSharedPointer<QCPGraphDataContainer> getData() const{return _data;};
    bool isVisible() const {return visible;}

    void setVisible(bool visible) ;

    bool operator==(const PlotData& other);
signals:
    void visibaleChanged(bool visible);
private:
    QSharedPointer<QCPGraphDataContainer> _data;
    QString name;//名字
    QString units;//单位
    bool  visible=true;
};


#endif //PLOT_PLOTDATA_H