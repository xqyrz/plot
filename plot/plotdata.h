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
    explicit PlotData(uint64_t,QSharedPointer<QCPGraphDataContainer> data,QColor color, const QString &name, const QString &units, QObject *parent = nullptr);
    ~PlotData() override = default;

    QString getName() const{return name;};
    QString getUnits() const{return units;};
    QString getShowData()const;
    QColor getColor() const{return color;};
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
    QColor color;//颜色
    const uint64_t id = 0;
    bool  visible=true;
};


#endif //PLOT_PLOTDATA_H