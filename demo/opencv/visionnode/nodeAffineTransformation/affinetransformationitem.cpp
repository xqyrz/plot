//
// Created by 25137 on 2026/11/8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AffineTransformationItem.h" resolved

#include "affinetransformationitem.h"
#include "ui_AffineTransformationItem.h"

#include "cal/opencvQT.h"
AffineTransformationItem::AffineTransformationItem(QWidget* parent) :
    QWidget(parent), ui(new Ui::AffineTransformationItem)
{
    ui->setupUi(this);
}

AffineTransformationItem::~AffineTransformationItem() { delete ui; }
void AffineTransformationItem::setMat(QString& code,QSize sz)
{
    OpencvCal cal;
    auto cmd = code.split("->");
    QStringList cmd_;
    cv::Mat M = cv::Mat::eye(3, 3, CV_64F);
    cv::Size size(sz.width(), sz.height());
    for (auto&var:cmd)
    {
        if (!var.contains(':'))continue;
        if (var.contains("moveX") )
        {
            bool ok =false;
            auto value = var.split(":").last().toDouble(&ok);
            if (!ok)continue;
           M= cal.move(value,0,size,M);
        }
        else if (var.contains("moveY"))
        {
            bool ok =false;
            auto value = var.split(":").last().toDouble(&ok);
            if (!ok)continue;
            M= cal.move(0,value,size,M);
        }
        else  if (var.contains("scaleX"))
        {
            bool ok =false;
            auto value = var.split(":").last().toDouble(&ok);
            if (!ok)continue;
            M= cal.scale(value,0,size,M);
        }
        else  if (var.contains("scaleY"))
        {
            bool ok =false;
            auto value = var.split(":").last().toDouble(&ok);
            if (!ok)continue;
            M= cal.scale(0,value,size,M);
        }
        else if (var.contains("angle"))
        {
            bool ok =false;
            auto value = var.split(":").last().toDouble(&ok);
            if (!ok)continue;
            M= cal.rotate(value,size,M);
        }
        else
        {
            continue;
        }
        cmd_.append(var);
    }
    std::copy(M.ptr<double>(0), M.ptr<double>(0) + 9, m_M.begin());
}
void AffineTransformationItem::on_moveX_valueChanged(double value)
{
    if (value*100 != ui->moveXSlider->value())
    {
        ui->moveXSlider->setValue(value*100);
    }
}
void AffineTransformationItem::on_moveXSlider_valueChanged(int value)
{
    if (value != ui->moveX->value()*100)
    {
        ui->moveX->setValue(value/100.0);
    }
}
void AffineTransformationItem::on_moveY_valueChanged(double value)
{
    if (value*100 != ui->moveYSlider->value())
    {
        ui->moveYSlider->setValue(value*100);
    }
}
void AffineTransformationItem::on_moveYSlider_valueChanged(int value)
{
    if (value != ui->moveY->value()*100)
    {
        ui->moveY->setValue(value/100.0);
    }
}
void AffineTransformationItem::on_scale_valueChanged(double value)
{
    if (value*100 != ui->scaleSlider->value())
    {
        ui->scaleSlider->setValue(value*100);
    }
}
void AffineTransformationItem::on_scaleSlider_valueChanged(int value)
{
    if (value != ui->scale->value()*100)
    {
        ui->scale->setValue(value/100.0);
    }
}
void AffineTransformationItem::on_angle_valueChanged(double value)
{
    if (value*100 != ui->angleSlider->value())
    {
        ui->angleSlider->setValue(value*100);
    }
}
void AffineTransformationItem::on_angleSlider_valueChanged(int value)
{
    if (value != ui->angle->value()*100)
    {
        ui->angle->setValue(value/100.0);
    }
}


