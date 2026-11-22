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
    case  COLOR_PLOT:
        if (auto node = plot->getPlotData(COLOR_PLOT))
        {d =node->plotData->getData();}
        else
        {
            d = QSharedPointer<QCPGraphDataContainer>::create();
            plot->add_plotData(COLOR_PLOT,d,"color_cnt",0,"#808088");
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
void HistogramItem::init()
{
    switch (ui->type->currentIndex())
    {
    case RGB:
        plot->showPlot(R_PLOT,true);
        plot->showPlot(G_PLOT,true);
        plot->showPlot(B_PLOT,true);
        plot->showPlot(COLOR_PLOT,false);
        break;
    case COLOR:
        plot->showPlot(R_PLOT,false);
        plot->showPlot(G_PLOT,false);
        plot->showPlot(B_PLOT,false);
        plot->showPlot(COLOR_PLOT,true);
        break;
    }
    emit cal((Type)(ui->type->currentIndex()));
}
int HistogramItem::num()
{
    return ui->num->value();
}
void HistogramItem::on_calBtn_clicked()
{
    switch (ui->type->currentIndex())
    {
    case RGB:
        plot->showPlot(R_PLOT,true);
        plot->showPlot(G_PLOT,true);
        plot->showPlot(B_PLOT,true);
        plot->showPlot(COLOR_PLOT,false);
        ui->numLabel->setVisible(false);
        ui->num->setVisible(false);
        break;
    case COLOR:
        plot->showPlot(R_PLOT,false);
        plot->showPlot(G_PLOT,false);
        plot->showPlot(B_PLOT,false);
        plot->showPlot(COLOR_PLOT,true);
        ui->numLabel->setVisible(TRUE);
        ui->num->setVisible(TRUE);
        break;
    }

    emit cal((Type)(ui->type->currentIndex()));
}
void HistogramItem::on_type_currentIndexChanged(int index)
{
    on_calBtn_clicked();
}
