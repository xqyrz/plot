//
// Created by 25137 on 2026/11/14.
//

#ifndef PLOT_GAMMA_H
#define PLOT_GAMMA_H

#include <QWidget>
class PlotView;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Gamma;
}
QT_END_NAMESPACE

class Gamma : public QWidget
{
    Q_OBJECT

public:
    explicit Gamma(QWidget* parent = nullptr);
    ~Gamma() override;

private:
    Ui::Gamma* ui;
    PlotView* plotView;
};


#endif // PLOT_GAMMA_H
