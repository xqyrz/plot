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
    // 第一步：定义枚举，值必须是 2 的幂
    enum ATFlag {

            MoveX  = 1 << 0,   //
            MoveY  = 1 << 1,   //
            ScaleX = 1 << 2,    //
            ScaleY = 1 << 3,
            Angle  = 1 << 5
        };
    Q_DECLARE_FLAGS(ATFlags, ATFlag)
public:
    explicit AffineTransformationItem(QWidget* parent = nullptr);
    ~AffineTransformationItem() override;
    void setMat(QString& dir,QSize);
     std::array<double,9> M()const{return m_M;};
    void setM(std::array<double,9> M);
    signals:
    void mChanged();
private slots:
    void on_moveX_valueChanged(double value);

    void on_moveXSlider_valueChanged(int value);

    void on_moveY_valueChanged(double value);

    void on_moveYSlider_valueChanged(int value);

    void on_scale_valueChanged(double value);

    void on_scaleSlider_valueChanged(int value);

    void on_angle_valueChanged(double value);

    void on_angleSlider_valueChanged(int value);
protected slots:
    void timerEvent(QTimerEvent* event) override;
private:
    Ui::AffineTransformationItem* ui;
    std::array<double,9> m_M;
    int timer50_id;
    ATFlags atFlags;
    QSize m_size;
};



#endif // PLOT_AFFINETRANSFORMATIONITEM_H
