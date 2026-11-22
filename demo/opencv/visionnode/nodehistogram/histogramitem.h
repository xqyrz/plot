//
// Created by 25137 on 2026/11/22.
//

#ifndef PLOT_HISTOGRAMITEM_H
#define PLOT_HISTOGRAMITEM_H

#include <QWidget>
#include "plotview.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class HistogramItem;
}
QT_END_NAMESPACE

class HistogramItem : public QWidget
{
    Q_OBJECT

public:
    typedef enum
    {
        RGB = 0,
        COLOR,
        BT601,          // 亮度直方图（Y = 0.114B + 0.587G + 0.299R）
        HSV,            // HSV 直方图（H∈[0,180)，S/V∈[0,256)），横轴 0~360（H 为色相角度）
        HLS             // HLS 直方图（H∈[0,180)，L/S∈[0,256)），横轴 0~360（H 为色相角度）
    }Type;
    typedef enum
    {
        R_PLOT = 0x0000000,
        G_PLOT = 0x0001000,
        B_PLOT = 0x0002000,
        L_PLOT = 0x0003000,   // BT.601 亮度
        COLOR_PLOT = 0x0005000,
        HSV_H_PLOT = 0x0006000,
        HSV_S_PLOT = 0x0007000,
        HSV_V_PLOT = 0x0008000,
        HLS_H_PLOT = 0x0009000,
        HLS_L_PLOT = 0x000A000,
        HLS_S_PLOT = 0x000B000
    }PlotEnum;
    explicit HistogramItem(QWidget* parent = nullptr);
    ~HistogramItem() override;

     QSharedPointer<QCPGraphDataContainer> data(PlotEnum);
    void clear();
    void init();
    int num();
private slots:
    void on_calBtn_clicked();
    void on_type_currentIndexChanged(int index);
    signals:
    void cal(Type type);
private:
    void applyType(int type);   // 按类型设置曲线显示/隐藏（init 与 cal 按钮共用）
private:
    Ui::HistogramItem* ui;
    PlotView* plot;
};


#endif // PLOT_HISTOGRAMITEM_H
