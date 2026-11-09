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
    timer50_id =startTimer(50);
    ui->setupUi(this);
}

AffineTransformationItem::~AffineTransformationItem() { delete ui; }
void AffineTransformationItem::setMat(QString& code,QSize sz)
{
    OpencvCal cal;
    m_size = sz;
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
void AffineTransformationItem::setM(std::array<double, 9> M)
{
    if (M != m_M)
    {
        m_M = M;
        emit mChanged();
    }
}
void AffineTransformationItem::on_moveX_valueChanged(double value)
{
    if (value*100 != ui->moveXSlider->value())
    {
        ui->moveXSlider->setValue(value*100);
        atFlags= MoveX;
    }
}
void AffineTransformationItem::on_moveXSlider_valueChanged(int value)
{
    if (value != ui->moveX->value()*100)
    {
        ui->moveX->setValue(value/100.0);
        atFlags= MoveX;
    }
}
void AffineTransformationItem::on_moveY_valueChanged(double value)
{
    if (value*100 != ui->moveYSlider->value())
    {
        ui->moveYSlider->setValue(value*100);
        atFlags= MoveY;
    }
}
void AffineTransformationItem::on_moveYSlider_valueChanged(int value)
{
    if (value != ui->moveY->value()*100)
    {
        ui->moveY->setValue(value/100.0);
        atFlags= ScaleX;
    }
}
void AffineTransformationItem::on_scale_valueChanged(double value)
{
    auto _value = ui->scaleSlider->value();
    if (_value>10000) _value = 1+(_value-10000)/10000.0;
    else _value = _value/1000.0;
    if (value*100 != ui->scaleSlider->value())
    {
        ui->scaleSlider->setValue(value*100);
        atFlags= ScaleY;
    }
}
void AffineTransformationItem::on_scaleSlider_valueChanged(int value)
{
    if (value != ui->scale->value()*100)
    {
        ui->scale->setValue(value/100.0);
        //updateM_Flag = true;
    }
}
void AffineTransformationItem::on_angle_valueChanged(double value)
{
    if (value*100 != ui->angleSlider->value())
    {
        ui->angleSlider->setValue(value*100);
        atFlags= Angle;
    }
}
void AffineTransformationItem::on_angleSlider_valueChanged(int value)
{
    if (value != ui->angle->value()*100)
    {
        ui->angle->setValue(value/100.0);
        //updateM_Flag = true;
    }
}
void AffineTransformationItem::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timer50_id)
    {
        if (atFlags)
        {
            cv::Mat M = cv::Mat::eye(3, 3, CV_64FC1);
            cv::Size size(m_size.width(), m_size.height());
            if (MoveX  != atFlags) M=VisionCal::move(ui->moveX->value(),0,size,M);
            if (MoveY  != atFlags) M=VisionCal::move(0,ui->moveY->value(),size,M);
            if (ScaleX != atFlags) M=VisionCal::scale(ui->scale->value(),ui->scale->value(),size,M);
            if (ScaleY != atFlags) M=VisionCal::scale(ui->scale->value(),ui->scale->value(),size,M);
            if (Angle  != atFlags) M=VisionCal::rotate(ui->angle->value(),size,M);
            switch (atFlags)
            {
            case MoveX :M=VisionCal::move(ui->moveX->value(),0,size,M);break;
            case MoveY :M=VisionCal::move(0,ui->moveY->value(),size,M);break;
            case ScaleX:M=VisionCal::scale(ui->scale->value(),ui->scale->value(),size,M);break;
            case ScaleY:M=VisionCal::scale(ui->scale->value(),ui->scale->value(),size,M);break;
            case Angle :M=VisionCal::rotate(ui->angle->value(),size,M);break;
            default:break;
            }
            atFlags = 0;
            std::array<double, 9> arr;
            std::copy_n(M.ptr<double>(), 9, arr.begin());
            setM(arr);
        }
    }
    QWidget::timerEvent(event);
}


