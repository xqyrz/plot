//
// Created by 25137 on 2026/11/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GammaItem.h" resolved

#include "gammaitem.h"
#include "ui_GammaItem.h"
#include <plotview.h>
#include "cal/opencvQT.h"
GammaItem::GammaItem(QWidget* parent) : QWidget(parent)
, ui(new Ui::GammaItem)
, m_plotView(new PlotView(this))
{
    ui->setupUi(this);
    layout()->addWidget(m_plotView->ui());
    m_plotView->onlyPlot(true);
     m_plotView->setZero(0);

}

GammaItem::~GammaItem() { delete ui; }
void GammaItem::clear()
{
    m_plotView->clear();
}
void GammaItem::setLut(std::vector<uint16_t>* _lut)
{

    lut = _lut;
    _updatePlot();
}
void GammaItem::setText(QString str)
{
    ui->text->setText(str);
}
void GammaItem::on_createBtn_clicked()
{
    emit lutCreate(ui->doubleSpinBox->value());
}
void GammaItem::_updatePlot()
{
    m_plotView->clear();
    QList<PLUG::_SIGNALS> datas;
    PLUG::_SIGNALS d;
    d.name ="gamma";
    d.id = 0;
    for (int i =0;i<lut->size();i++)
    {
        d.time = i;
        d.value = lut->at(i);
        datas.append(d);
    }
    m_plotView->_addSignalData(datas);
    emit updatePlot();
}
