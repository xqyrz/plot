//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_AFFINETRANSFORMATIONITEM_H
#define PLOT_AFFINETRANSFORMATIONITEM_H

#include <QWidget>
#include <array>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class AffineTransformationItem;
}
QT_END_NAMESPACE

class AffineTransformationItem : public QWidget
{
    Q_OBJECT

public:
    explicit AffineTransformationItem(QWidget* parent = nullptr);
    ~AffineTransformationItem() override;

    void setMat(QString& dir,QSize);
    const std::array<double,9> M()const{return m_M;};
private slots:
    void on_moveX_valueChanged(double value);

    void on_moveXSlider_valueChanged(int value);

    void on_moveY_valueChanged(double value);

    void on_moveYSlider_valueChanged(int value);

    void on_scale_valueChanged(double value);

    void on_scaleSlider_valueChanged(int value);

    void on_angle_valueChanged(double value);

    void on_angleSlider_valueChanged(int value);
private:
    Ui::AffineTransformationItem* ui;
    std::array<double,9> m_M;
};



#endif // PLOT_AFFINETRANSFORMATIONITEM_H
