//
// Created by 25137 on 25-9-27.
//

#include "plotcustom.h"
#include "plotcommon.h"
#include <QTimer>
#include <QOpenGLWidget>

PlotCustom::PlotCustom(QWidget* parent)
    : QCustomPlot(parent)
      , _updateTimer(new QTimer(this))
      , _resetUITimer(new QTimer(this))
{
    _initUI();
    _resetUITimer->setSingleShot(true);
    connect(_updateTimer, &QTimer::timeout, this, [&]()
    {
        _updateTimerEn = true;
        if (this->isVisible())
        {
            this->replot(QCustomPlot::rpQueuedReplot);
        }
    });
    connect(_resetUITimer, &QTimer::timeout, this, &PlotCustom::_resetUI);

    _updateTimer->start(40);
}

void PlotCustom::resetUI(PlotModel* model)
{
    if (model)
    {
        _model = model;
    }
    _resetUITimer->start(1);
}

void PlotCustom::setPlotType(int type)
{
    plotType = type;
    _resetUI();
}

void PlotCustom::setCurrentPlot(int type, const QCPLayerable* item)
{
    qDebug() << "setCurrentPlot" << type; //<<item;
    QCPAxisRect* axisRect = nullptr;
    QCPAxis* _xAxis = nullptr;
    QCPAxis* _yAxis = nullptr;
    switch (type)
    {
    case PLOT::ITEM_GRAPH:
        {
            auto graph = qobject_cast<const QCPGraph*>(item);
            _xAxis = graph->keyAxis();
            _yAxis = graph->valueAxis();
            axisRect = _yAxis->axisRect();
        }
        break;
    case PLOT::ITEM_AXIS:
        {
            auto axis = qobject_cast<const QCPAxis*>(item);
            if (axis->axisType() == QCPAxis::atLeft)
            {
                _yAxis = const_cast<QCPAxis*>(axis);
                axisRect = axis->axisRect();
                _xAxis = axisRect->axis(QCPAxis::atBottom);
            }
        }
        break;
    default: break;
    }
    if ((axisRect != nullptr)
        && (_xAxis != nullptr)
        && (_yAxis != nullptr))
    {
        axisRect->setRangeZoomAxes(_xAxis, _yAxis); //设置缩放的绑定轴
        axisRect->setRangeDragAxes(_xAxis, _yAxis); //设置拖拽的绑定轴


        switch (plotType)
        {
        case PLOT::TYPE_oneXoneY:
            {
               if (_model)
               {
                   if ( type ==PLOT::ITEM_GRAPH){}
                   auto graph = qobject_cast<const QCPGraph*>(item);
                   auto plot = _model->getPlot(graph->data());
                   _yAxis->setLabelColor(plot->plotData->getColor());
                   _yAxis->setTickLabelColor(plot->plotData->getColor());
                   _yAxis->setLabel(plot->plotData->getName());
               }
            }
            break;
        case PLOT::TYPE_oneXmoreY:

            break;
        default: break;
        }
    }
    emit pressedPlot(type, item);
}

void PlotCustom::setTicks()
{
}

void PlotCustom::_resizeEvent()
{
    //qInfo()<<"resizeEvent"<<event->size();
    int interval = plotType == PLOT::TYPE_moreXmoreY ? 60 : 60;
    auto rects = this->axisRects();
    for (QCPAxisRect* rect : rects)
    {
        // qDebug() << "AxisRect rect:" << rect->rect().size();
        auto width = rect->width();
        auto height = rect->height();
        auto x_axis = rect->axes(QCPAxis::atBottom);
        auto y_axis = rect->axes(QCPAxis::atLeft);
        for (auto axis : x_axis)
        {
            axis->ticker()->setTickCount(width / interval ? width / interval : 3); // 启用自动刻度
        }
        for (auto axis : y_axis)
        {
            axis->ticker()->setTickCount(height / interval ? height / interval : 3); // 启用自动刻度
        }
    }
}

void PlotCustom::resizeEvent(QResizeEvent* event)
{
    QCustomPlot::resizeEvent(event);
    _resizeEvent();
}

void PlotCustom::contextMenuEvent(QContextMenuEvent* event)
{
    // 创建一个菜单
    QMenu menu(this);
    // 添加菜单项
    QAction* autoAction = menu.addAction(QString("自适应"));
    QAction* saveAction = menu.addAction("Save");
    QAction* exitAction = menu.addAction("Exit");

    // 显示菜单，并获取用户选择的菜单项
    QAction* selectedAction = menu.exec(event->globalPos());

    // 根据用户选择的菜单项执行相应的操作
    if (selectedAction == autoAction)
    {
        for (auto i = 0; i < this->graphCount(); i++)
        {
            this->graph(i)->rescaleAxes();
        }
    }
    else if (selectedAction == saveAction)
    {
        // 执行保存操作
    }
    else if (selectedAction == exitAction)
    {
        // 执行退出操作
        QApplication::quit();
    }
}

void PlotCustom::mousePressEvent(QMouseEvent* event)
{
    QCustomPlot::mousePressEvent(event);
    QVariant info;
    auto obj = layerableAt(event->pos(), true, &info); //查找特定像素位置处的顶层可图层对象（QCPLayerable）的函数
    if (!obj) return;
    // 获取鼠标点击位置的轴
    if (info.canConvert<QCPAxis::SelectablePart>()) //		// 找到了一个轴，可以进行进一步处理
    {
        auto axis = qobject_cast<QCPAxis*>(obj);
        //qDebug()<<"axis:"<<axis;
        setCursor(Qt::ClosedHandCursor); //设置鼠标形状
        if (axis->orientation() == Qt::Vertical)
        {
        }
        setCurrentPlot(PLOT::ITEM_AXIS, obj);
    }
    else if ((info.canConvert<QCPDataSelection>())) // 找到了一个曲线，可以进行进一步处理
    {
        auto graph = qobject_cast<QCPGraph*>(obj);
        //qDebug()<<"graph:"<<graph;
        setCursor(Qt::SizeAllCursor);
        setCurrentPlot(PLOT::ITEM_GRAPH, obj);
    }
    else if (qobject_cast<QCPItemStraightLine*>(obj))
    {
        _line_flag = true;
        //无限延长的线
        setCursor(Qt::SizeHorCursor);
    }
    else
    {
        qDebug() << "Clicked on something else:" << info;
    }
}


void PlotCustom::mouseReleaseEvent(QMouseEvent* event)
{
    _line_flag = false;
    setCursor(Qt::ArrowCursor);
    QCustomPlot::mouseReleaseEvent(event);
}

void PlotCustom::mouseMoveEvent(QMouseEvent* event)
{
    if (!_line || !_line_flag)
    {
        QCustomPlot::mouseMoveEvent(event);
        return;
    }

    auto axisRects = this->axisRects();

    for (auto rect : axisRects)
    {
        // 获取 x 坐标对应数据坐标
        auto xAxis = rect->axis(QCPAxis::atBottom);
        double x = xAxis->pixelToCoord(event->pos().x());

        // 更新垂直参考线位置
        if (_line)
        {
            _line->point1->setCoords(x, 0);
            _line->point2->setCoords(x, 1);
        }

        // 遍历 items
        for (auto item : rect->items())
        {
            if (auto tracer = qobject_cast<QCPItemTracer*>(item))
            {
                tracer->setGraphKey(x); // 更新 tracer
                _tracerMap.value(tracer)->setText(QString("y:%1").arg(tracer->position->value()));
            }
        }
    }
}


void PlotCustom::_initUI()
{
    setBackground(QColor(234, 234, 234));

    setOpenGl(true, 2000);
    setNotAntialiasedElements(QCP::aeAll);
    setNoAntialiasingOnDrag(true);

    //    qInfo()<<"opengl:"<<this->openGl();
    _line = nullptr;
    _tracerMap.clear();
    plotLayout()->clear();
    this->clearGraphs();
    this->clearItems();
    this->clearPlottables();

    //   setMaximumSize(QSize(0, 0));
    this->setInteractions(
        //     QCP::iSelectPlottables |
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
void PlotCustom::_initQCPGraph(QCPAxisRect* axisRect,QCPGraph * graph,QColor color)
{
    auto _tracer = new QCPItemTracer(this);
    _tracer->setClipAxisRect(axisRect);
    _tracer->setStyle(QCPItemTracer::tsCircle);
    _tracer->setSize(3);
    _tracer->setPen(QPen(Qt::black));
    _tracer->setBrush(QBrush(Qt::NoBrush));
    _tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
    _tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
    // 绑定曲线，只在曲线的数据点上出现
    _tracer->setGraph(graph);
   // _tracer->setVisible(false);//默认隐藏

    auto _label = new QCPItemText(this);
    _label->setClipAxisRect(axisRect);
    _label->setPadding(QMargins(3, 3, 3, 3));
    _label->setPen(QPen(Qt::black));
    _label->setBrush(QBrush(color));
    if (color.lightness() > 80) {
        _label->setColor(Qt::black);
    }
    else {
        _label->setColor(Qt::white);
    }
    _label->setText("");
    _label->setTextAlignment(Qt::AlignLeft);
    _label->setPositionAlignment(Qt::AlignRight);
    _label->position->setParentAnchor(_tracer->position);

    // 初始化显示坐标
    _label->setText(QString("y:%1").arg(_tracer->position->value()));




    _tracerMap.insert(_tracer,_label);


    //connect(infLine,&QCPItemStraightLine::)

    graph->setAdaptiveSampling(true);
    // 设置曲线样式
    graph->setPen(QPen(color)); // 线颜色
    graph->setLineStyle(QCPGraph::lsLine); // 折线
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, color,
                                          color, 2));
}
void PlotCustom::_initAxis(QCPAxisRect* axisRect, QCPAxis* _xAxis, QCPAxis* _yAxis)
{
    _yAxis->setOffset(0);
    _yAxis->setLabelPadding(0);
    _yAxis->setTickLabelPadding(10);
    // QFont font;
    // font.setPointSize(10);
    // _yAxis->setLabelFont(font);
    // _yAxis->setTickLabelFont(font);

    // 配置网格线
    _yAxis->grid()->setVisible(true);
    _yAxis->grid()->setSubGridVisible(false);
    //_yAxis->setTickLabelSide(QCPAxis::lsInside);





    axisRect->setAutoMargins(QCP::MarginSide::msLeft | QCP::MarginSide::msRight);
    axisRect->setRangeDrag(Qt::Horizontal | Qt::Vertical); //水平方向拖动
    axisRect->setRangeZoom(Qt::Horizontal | Qt::Vertical); //水平方向缩放
    axisRect->setMargins(QMargins(0, 0, 0, 20));
    axisRect->setRangeZoomFactor(0.85); // 设置缩放因子，小于1表示缩小，大于1表示放大
    axisRect->setRangeZoomAxes(_xAxis, _yAxis); //设置缩放的绑定轴
    axisRect->setRangeDragAxes(_xAxis, _yAxis); //设置拖拽的绑定轴
    // 配置轴的边距
    axisRect->setAutoMargins(QCP::msAll);

    axisRect->axis(QCPAxis::atLeft)->grid()->setZeroLinePen(Qt::NoPen);

    //connect(_xAxis,QOverload<const QCPRange &>(&QCPAxis::rangeChanged),this,&PlotCustom::setTicks);
}

QCPGraph* PlotCustom::_oneXoneY()
{
    QCPGraph* graph = nullptr;
    _initUI();
    if (_model == nullptr)
    {
        return graph;
    }
    auto root = _model->root();
    auto marginGroup = new QCPMarginGroup(this);
    auto axisRect = new QCPAxisRect(this, false);
    this->plotLayout()->addElement(0, 0, axisRect);
    axisRect->setMarginGroup(QCP::msLeft, marginGroup);
    auto _xAxis = axisRect->addAxis(QCPAxis::atBottom);

    QCPAxis* _yAxis = axisRect->addAxis(QCPAxis::atLeft);

    for (auto const& group : *root)
    {
        for (auto const& plot : *group)
        {
            if (!plot->plotData->isVisible()) { continue; }


            _yAxis->setLabel((plot->plotData->getName()));
            _initAxis(axisRect, _xAxis, _yAxis);
            // 创建曲线
            graph = this->addGraph(_xAxis, _yAxis);
            graph->setData(plot->plotData->getData());
            _initQCPGraph(axisRect,graph,plot->plotData->getColor());

            _yAxis->setLabelColor(plot->plotData->getColor());
            _yAxis->setTickLabelColor(plot->plotData->getColor());

            //  graph->rescaleAxes();
        }
    }
    QTimer::singleShot(1, this, [=]()
    {
        for (auto i = 0; i < this->graphCount(); i++)
        {
            this->graph(i)->rescaleAxes();
        }
    });
    return graph;
}

QCPGraph* PlotCustom::_oneXmoreY()
{
    QCPGraph* graph = nullptr;
    _initUI();
    if (_model == nullptr)
    {
        return graph;
    }
    auto root = _model->root();
    auto marginGroup = new QCPMarginGroup(this);
    auto axisRect = new QCPAxisRect(this, false);
    this->plotLayout()->addElement(0, 0, axisRect);
    auto _xAxis = axisRect->addAxis(QCPAxis::atBottom);

    for (auto const& group : *root)
    {
        for (auto const& plot : *group)
        {
            if (!plot->plotData->isVisible()) { continue; }
            auto _yAxis = axisRect->addAxis(QCPAxis::atLeft);
            _yAxis->setLabel((plot->plotData->getName()));
            axisRect->setMarginGroup(QCP::msLeft, marginGroup);
            _initAxis(axisRect, _xAxis, _yAxis);
            // 创建曲线
            graph = this->addGraph(_xAxis, _yAxis);
            _initQCPGraph(axisRect,graph,plot->plotData->getColor());

            graph->setData(plot->plotData->getData());

            _yAxis->setLabelColor(plot->plotData->getColor());
            _yAxis->setTickLabelColor(plot->plotData->getColor());
            //  graph->rescaleAxes();
        }
    }
    QTimer::singleShot(1, this, [=]()
    {
        for (auto i = 0; i < this->graphCount(); i++)
        {
            this->graph(i)->rescaleAxes();
        }
    });
    return graph;
}

QCPGraph* PlotCustom::_moreXmoreY()
{
    QCPGraph* graph = nullptr;
    _initUI();
    if (_model == nullptr)
    {
        return graph;
    }
    auto root = _model->root();
    auto marginGroup = new QCPMarginGroup(this);

    int i = 0;
    for (auto const& group : *root)
    {
        for (auto const& plot : *group)
        {
            if (!plot->plotData->isVisible()) { continue; }
            auto axisRect = new QCPAxisRect(this, false);
            this->plotLayout()->addElement(i, 0, axisRect);
            auto _xAxis = axisRect->addAxis(QCPAxis::atBottom);
            auto _yAxis = axisRect->addAxis(QCPAxis::atLeft);
            _yAxis->setLabel((plot->plotData->getName()));
            axisRect->setMarginGroup(QCP::msLeft, marginGroup);
            _initAxis(axisRect, _xAxis, _yAxis);
            // 创建曲线
            graph = this->addGraph(_xAxis, _yAxis);
            _initQCPGraph(axisRect,graph,plot->plotData->getColor());


            graph->setData(plot->plotData->getData());

            _yAxis->setLabelColor(plot->plotData->getColor());
            _yAxis->setTickLabelColor(plot->plotData->getColor());

            i++;
        }
    }
    for (auto i = 0; i < this->graphCount(); i++)
    {
        for (auto j = 0; j < this->graphCount(); j++)
        {
            if (i == j) { continue; }
            connect(this->graph(i)->keyAxis(), QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged),
                    this->graph(j)->keyAxis(), QOverload<const QCPRange&>::of(&QCPAxis::setRange));
        }
    }
    QTimer::singleShot(1, this, [=]()
    {
        for (auto i = 0; i < this->graphCount(); i++)
        {
            this->graph(i)->rescaleAxes();
        }
    });
    return graph;
}

void PlotCustom::_resetUI()
{
    QCPGraph* graph = nullptr;

    switch (plotType)
    {
    case PLOT::TYPE_oneXoneY:
        graph =_oneXoneY();
        break;
    case PLOT::TYPE_oneXmoreY:
        graph =_oneXmoreY();
        break;
    case PLOT::TYPE_moreXmoreY:
        graph =_moreXmoreY();
        break;
    default:
        break;
    }


    if (graph)
    {
         _line = new QCPItemStraightLine(this);
        _line->setPen(QPen(Qt::blue, 2, Qt::SolidLine));
        _line->setSelectable(true);
        if (graph->data()->size())
        {
            _line->point1->setCoords(graph->data()->at(0)->key,0);   // 直线上的点 (x=0,y=2)
            _line->point2->setCoords(graph->data()->at(0)->key, 1);   // 方向：水平线
        }
    }
    QTimer::singleShot(100, this, [=]()
    {
        _resizeEvent();
    });
}
