//
// Created by 25137 on 25-9-27.
//

#ifndef PLOTCUSTOM_H
#define PLOTCUSTOM_H

#include <qcustomplot/qcustomplot.h>
#include "plotmodel.h"
class PlotCustom:public QCustomPlot{
    Q_OBJECT
public:
    explicit PlotCustom(QWidget *parent = nullptr);
    void resetUI( PlotModel* model);
protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    void _initUI();
private:
   QTimer* _updateTimer;
    bool _updateTimerEn;
};



#endif //PLOTCUSTOM_H
