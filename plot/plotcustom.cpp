//
// Created by 25137 on 25-9-27.
//

#include "plotcustom.h"
#include "plotcommon.h"
#include <QTimer>
PlotCustom::PlotCustom(QWidget *parent)
:QCustomPlot(parent)
,_updateTimer(new QTimer(this))
,_resetUITimer(new QTimer(this)) {
    _initUI();
    _resetUITimer->setSingleShot(true);
    connect(_updateTimer, &QTimer::timeout, this, [&]() {
        _updateTimerEn = true;
        if(this->isVisible()) {
            this->replot(QCustomPlot::rpQueuedReplot);
        }
    });
     connect(_resetUITimer, &QTimer::timeout, this, &PlotCustom::_resetUI);
    _updateTimer->start(20);
}

void PlotCustom::resetUI( PlotModel *model) {
    _model = model;
    _resetUITimer->start(1);
}

void PlotCustom::setPlotType(int type) {
    plotType = type;
    _resetUI();
}

void PlotCustom::contextMenuEvent(QContextMenuEvent *event) {
    // 创建一个菜单
    QMenu menu(this);
    // 添加菜单项
    QAction* autoAction = menu.addAction(QString("自适应"));
    QAction* saveAction = menu.addAction("Save");
    QAction* exitAction = menu.addAction("Exit");

    // 显示菜单，并获取用户选择的菜单项
    QAction* selectedAction = menu.exec(event->globalPos());

    // 根据用户选择的菜单项执行相应的操作
    if (selectedAction == autoAction) {
        for (auto i = 0; i < this->graphCount(); i++) {
            this->graph(i)->rescaleAxes();
        }
    }
    else if (selectedAction == saveAction) {
        // 执行保存操作
    }
    else if (selectedAction == exitAction) {
        // 执行退出操作
        QApplication::quit();
    }
}

void PlotCustom::_initUI() {
    plotLayout()->clear();
    this->clearGraphs();
    this->clearItems();
    this->clearPlottables();

    //   setMaximumSize(QSize(0, 0));


    this->setInteractions(
        QCP::iSelectPlottables |
        QCP::iSelectAxes |
        QCP::iSelectLegend |
        QCP::iSelectItems |
        QCP::iMultiSelect |
        QCP::iRangeDrag |
        QCP::iRangeZoom
    );
    this->plotLayout()->setColumnSpacing(0);
    this->plotLayout()->setRowSpacing(0);
    this->plotLayout()->setWrap(1);
}

void PlotCustom::_initAxis(QCPAxisRect *axisRect, QCPAxis *_xAxis, QCPAxis *_yAxis) {
    axisRect->setAutoMargins(QCP::MarginSide::msLeft | QCP::MarginSide::msRight);
    axisRect->setRangeDrag(Qt::Horizontal | Qt::Vertical); //水平方向拖动
    axisRect->setRangeZoom(Qt::Horizontal | Qt::Vertical); //水平方向缩放
    axisRect->setMargins(QMargins(0, 0, 0, 20));
    axisRect->setRangeZoomFactor(0.85); // 设置缩放因子，小于1表示缩小，大于1表示放大
    axisRect->setRangeZoomAxes(_xAxis, _yAxis);//设置缩放的绑定轴
    axisRect->setRangeDragAxes(_xAxis, _yAxis);//设置拖拽的绑定轴
    // 配置轴的边距
    axisRect->setAutoMargins(QCP::msAll);

    axisRect->axis(QCPAxis::atLeft)->grid()->setZeroLinePen(Qt::NoPen);
}

void PlotCustom::_oneXoneY() {
    _initUI();
    if (_model == nullptr) {
        return;
    }
    auto root = _model->root();
    auto marginGroup = new QCPMarginGroup(this);
    auto axisRect = new QCPAxisRect(this,false);
    this->plotLayout()->addElement(0,0, axisRect);

    auto _xAxis = axisRect->addAxis(QCPAxis::atBottom);
    auto _yAxis = axisRect->addAxis(QCPAxis::atLeft);


    axisRect->setMarginGroup(QCP::msLeft, marginGroup);
    _initAxis(axisRect, _xAxis, _yAxis);


    for (auto const& group: *root) {
        for (auto const& plot:*group) {
            // 创建曲线
            auto graph = this->addGraph(_xAxis, _yAxis);

            graph->setData(plot->plotData->getData());
            // 设置曲线样式
            graph->setPen(QPen(plot->plotData->getColor()));    // 线颜色
            graph->setLineStyle(QCPGraph::lsLine); // 折线
            //  graph->rescaleAxes();
        }
    }
    QTimer::singleShot(100, this, [=]() {
        for (auto i = 0; i < this->graphCount(); i++) {
            this->graph(i)->rescaleAxes();
        }
    });
}

void PlotCustom::_oneXmoreY() {
    _initUI();
    if (_model == nullptr) {
        return;
    }
    auto root = _model->root();
    auto marginGroup = new QCPMarginGroup(this);
    auto axisRect = new QCPAxisRect(this,false);
    this->plotLayout()->addElement(0,0, axisRect);
    auto _xAxis = axisRect->addAxis(QCPAxis::atBottom);

    for (auto const& group: *root) {

        for (auto const& plot:*group) {
            auto _yAxis = axisRect->addAxis(QCPAxis::atLeft);
            axisRect->setMarginGroup(QCP::msLeft, marginGroup);
            _initAxis(axisRect, _xAxis, _yAxis);
            // 创建曲线
            auto graph = this->addGraph(_xAxis,_yAxis);

            graph->setData(plot->plotData->getData());
            // 设置曲线样式
            graph->setPen(QPen(plot->plotData->getColor()));    // 线颜色
            graph->setLineStyle(QCPGraph::lsLine); // 折线
            //  graph->rescaleAxes();
        }
    }
    QTimer::singleShot(100, this, [=]() {
        for (auto i = 0; i < this->graphCount(); i++) {
            this->graph(i)->rescaleAxes();
        }
    });
}

void PlotCustom::_moreXmoreY() {
    _initUI();
    if (_model == nullptr) {
        return;
    }
    auto root = _model->root();
    auto marginGroup = new QCPMarginGroup(this);

    int i=0;
    for (auto const& group: *root) {

        for (auto const& plot:*group) {
            auto axisRect = new QCPAxisRect(this,false);
            this->plotLayout()->addElement(i,0, axisRect);
            auto _xAxis = axisRect->addAxis(QCPAxis::atBottom);
            auto _yAxis = axisRect->addAxis(QCPAxis::atLeft);
            axisRect->setMarginGroup(QCP::msLeft, marginGroup);
            _initAxis(axisRect, _xAxis, _yAxis);
            // 创建曲线
            auto graph = this->addGraph(_xAxis,_yAxis);

            graph->setData(plot->plotData->getData());
            // 设置曲线样式
            graph->setPen(QPen(plot->plotData->getColor()));    // 线颜色
            graph->setLineStyle(QCPGraph::lsLine); // 折线

            i++;
        }
    }
    QTimer::singleShot(100, this, [=]() {
        for (auto i = 0; i < this->graphCount(); i++) {
            this->graph(i)->rescaleAxes();
        }
    });
}

void PlotCustom::_resetUI() {
    switch (plotType) {
    case PLOT::TYPE_oneXoneY:
        _oneXoneY();
        break;
    case PLOT::TYPE_oneXmoreY:
        _oneXmoreY();
        break;
    case PLOT::TYPE_moreXmoreY:
        _moreXmoreY();
        break;
    default:
        break;
    }
}
