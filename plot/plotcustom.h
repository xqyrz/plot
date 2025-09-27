//
// Created by 25137 on 25-9-27.
//

#ifndef PLOTCUSTOM_H
#define PLOTCUSTOM_H

#include <qcustomplot/qcustomplot.h>
#include "plotmodel.h"
class QTimer;
class PlotCustom:public QCustomPlot{
    Q_OBJECT
public:
    explicit PlotCustom(QWidget *parent = nullptr);
    void resetUI( PlotModel* model=nullptr);
    int getPlotType()const{ return plotType; }
public slots:
    void setPlotType(int type);
protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    void _initUI();
    void _initAxis(QCPAxisRect*,QCPAxis *horizontal, QCPAxis *vertical);
    void _oneXoneY();
    void _oneXmoreY();
    void _moreXmoreY();
    void _resetUI();
private:
   QTimer* _updateTimer;
    QTimer* _resetUITimer;
    bool _updateTimerEn;
    PlotModel* _model;
    int plotType;
private:
    // Q_PROPERTY(int getPlotType READ plotType WRITE setPlotType)
};



#endif //PLOTCUSTOM_H
