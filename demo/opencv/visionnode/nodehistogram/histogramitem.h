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
        COLOR
    }Type;
    typedef enum
    {
        R_PLOT = 0x0000000,
        G_PLOT = 0x0001000,
        B_PLOT = 0x0002000,
        COLOR_PLOT = 0x0005000
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
    Ui::HistogramItem* ui;
    PlotView* plot;
};


#endif // PLOT_HISTOGRAMITEM_H
