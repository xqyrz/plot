//
// Created by 25137 on 2026/11/15.
//

#ifndef PLOT_GAMMAITEM_H
#define PLOT_GAMMAITEM_H

#include <QWidget>

class PlotView;
QT_BEGIN_NAMESPACE
namespace Ui
{
    class GammaItem;
}
QT_END_NAMESPACE

class GammaItem : public QWidget
{
    Q_OBJECT

public:
    explicit GammaItem(QWidget* parent = nullptr);
    ~GammaItem() override;
    void clear();
    void setLut(std::vector<uint16_t>*);
    void setText(QString);
signals:
    void lutCreate(double);
    void updatePlot();
private slots:
    void on_createBtn_clicked();
private:
    void _updatePlot();
private:
    Ui::GammaItem* ui;
    PlotView* m_plotView;
    std::vector<uint16_t> *lut{nullptr};
    QSize imgSize;
};


#endif // PLOT_GAMMAITEM_H
