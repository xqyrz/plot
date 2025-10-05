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
signals:
    void pressedPlot( int type,const QCPLayerable * item);
public slots:
    void enupRang(){upRang = true;};
    void setPlotType(int type);
    void setCurrentPlot(int type, const QCPLayerable *item);
    void setXInterval(int interval){
        xInterval = interval;
    }
    void setXCheckBox(bool flag){
        _xCheckBox = flag;
    }
private slots:
    void setTicks();
    void _resizeEvent();
    void _replot();
protected:
    void resizeEvent(QResizeEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;//右键菜单
    void mousePressEvent(QMouseEvent* event) override;//鼠标按下
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event)override;
private:
    void _initUI();
    void _initAxis(QCPAxisRect*,QCPAxis *horizontal, QCPAxis *vertical);
    void _initQCPGraph(QCPAxisRect*,QCPGraph *,QColor color);
    void _resetUI();


    QCPGraph* _oneXoneY();
    QCPGraph* _oneXmoreY();
    QCPGraph* _moreXmoreY();
private:
   QTimer* _updateTimer;
    QTimer* _resetUITimer;
    bool _updateTimerEn;
    PlotModel* _model{nullptr};
    QCPItemStraightLine* _line{nullptr};
    int plotType{0};
    bool _line_flag{false};
    QMap<QCPItemTracer*,QCPItemText*> _tracerMap;
    int xInterval{100};
    bool upRang = false;
    bool _xCheckBox{true};
private:
    // Q_PROPERTY(int getPlotType READ plotType WRITE setPlotType)
};



#endif //PLOTCUSTOM_H
