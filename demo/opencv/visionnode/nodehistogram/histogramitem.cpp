//
// Created by 25137 on 2026/11/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_HistogramItem.h" resolved

#include "histogramitem.h"
#include "ui_HistogramItem.h"


HistogramItem::HistogramItem(QWidget* parent) :
QWidget(parent)
, ui(new Ui::HistogramItem)
,plot(new PlotView(this))
{
    ui->setupUi(this);
    ui->numLabel->setVisible(false);
    ui->num->setVisible(false);
   layout()->addWidget(plot->ui());
    plot->onlyPlot(true);
    plot->setZero(0);
}

HistogramItem::~HistogramItem() { delete ui; }
 QSharedPointer<QCPGraphDataContainer> HistogramItem::data(PlotEnum _id)
{
    QSharedPointer<QCPGraphDataContainer> d;
    QCPGraphData value;
    switch (_id)
    {
    case R_PLOT:
        if (auto node = plot->getPlotData(R_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
           plot->add_plotData(R_PLOT,d,"R_cnt",0,"#801010");
        }
        break;
    case  G_PLOT:
        if (auto node = plot->getPlotData(G_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(G_PLOT,d,"G_cnt",0,"#108010");
        }
        break;
    case  B_PLOT:
        if (auto node = plot->getPlotData(B_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(B_PLOT,d,"B_cnt",0,"#101080");
        }
        break;
    case  L_PLOT:
        if (auto node = plot->getPlotData(L_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(L_PLOT,d,"Y_cnt",0,"#808080");
        }
        break;
    case  COLOR_PLOT:
        if (auto node = plot->getPlotData(COLOR_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(COLOR_PLOT,d,"color_cnt",0,"#808088");
        }
        break;
    case  HSV_H_PLOT:
        if (auto node = plot->getPlotData(HSV_H_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(HSV_H_PLOT,d,"HSV_H_cnt",0,"#C07020");
        }
        break;
    case  HSV_S_PLOT:
        if (auto node = plot->getPlotData(HSV_S_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(HSV_S_PLOT,d,"HSV_S_cnt",0,"#20A0B0");
        }
        break;
    case  HSV_V_PLOT:
        if (auto node = plot->getPlotData(HSV_V_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(HSV_V_PLOT,d,"HSV_V_cnt",0,"#A0A020");
        }
        break;
    case  HLS_H_PLOT:
        if (auto node = plot->getPlotData(HLS_H_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(HLS_H_PLOT,d,"HLS_H_cnt",0,"#20B080");
        }
        break;
    case  HLS_L_PLOT:
        if (auto node = plot->getPlotData(HLS_L_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(HLS_L_PLOT,d,"HLS_L_cnt",0,"#B04080");
        }
        break;
    case  HLS_S_PLOT:
        if (auto node = plot->getPlotData(HLS_S_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(HLS_S_PLOT,d,"HLS_S_cnt",0,"#6060C0");
        }
        break;
        default:break;
    }
    return d;
}
void HistogramItem::clear()
{
    plot->clear();
}
void HistogramItem::applyType(int type)
{
    // 所有可能的曲线，先统一关掉（不存在的不动，避免无效告警）
    const PlotEnum allPlots[] = {
        R_PLOT, G_PLOT, B_PLOT, L_PLOT, COLOR_PLOT,
        HSV_H_PLOT, HSV_S_PLOT, HSV_V_PLOT,
        HLS_H_PLOT, HLS_L_PLOT, HLS_S_PLOT
    };
    for (auto p : allPlots)
    {
        if (plot->getPlotData(p))
            plot->showPlot(p, false);
    }

    switch (type)
    {
    case RGB:
        data(R_PLOT);   // 不存在就先建出来，保证 showPlot 生效
        data(G_PLOT);
        data(B_PLOT);
        plot->showPlot(R_PLOT,true);
        plot->showPlot(G_PLOT,true);
        plot->showPlot(B_PLOT,true);
        break;
    case COLOR:
        data(COLOR_PLOT);
        plot->showPlot(COLOR_PLOT,true);
        break;
    case BT601:
        data(L_PLOT);
        plot->showPlot(L_PLOT,true);
        break;
    case HSV:
        data(HSV_H_PLOT);
        data(HSV_S_PLOT);
        data(HSV_V_PLOT);
        plot->showPlot(HSV_H_PLOT,true);
        plot->showPlot(HSV_S_PLOT,true);
        plot->showPlot(HSV_V_PLOT,true);
        break;
    case HLS:
        data(HLS_H_PLOT);
        data(HLS_L_PLOT);
        data(HLS_S_PLOT);
        plot->showPlot(HLS_H_PLOT,true);
        plot->showPlot(HLS_L_PLOT,true);
        plot->showPlot(HLS_S_PLOT,true);
        break;
    default:
        break;
    }

    // 区间数对全部类型都有效
    ui->numLabel->setVisible(true);
    ui->num->setVisible(true);
}
void HistogramItem::init()
{
    applyType(ui->type->currentIndex());
    emit cal((Type)(ui->type->currentIndex()));
}
int HistogramItem::num()
{
    return ui->num->value();
}
void HistogramItem::on_calBtn_clicked()
{
    applyType(ui->type->currentIndex());
    emit cal((Type)(ui->type->currentIndex()));
}
void HistogramItem::on_type_currentIndexChanged(int index)
{
    on_calBtn_clicked();
}
