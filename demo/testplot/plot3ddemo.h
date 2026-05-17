#ifndef PLOT3DDEMO_H
#define PLOT3DDEMO_H

#include <QMainWindow>
#include <qwt3d_plot.h>
#include <qwt3d_function.h>

class Plot3DDemo : public QMainWindow
{
    Q_OBJECT
public:
    explicit Plot3DDemo(QWidget *parent = nullptr);

private:
    // 初始化 3D 绘图控件
    void initPlot3D();

    // 3D 绘图对象
    Qwt3D::Plot3D* m_plot3d;
};

// 自定义 3D 函数（生成曲面数据）
class My3DFunction : public Qwt3D::Function
{
public:
    My3DFunction(Qwt3D::Plot3D* plot) : Qwt3D::Function(plot) {}

    // 核心：计算 z = f(x,y) 的值
    double operator()(double x, double y) override
    {
        // 示例：正弦波纹曲面
        return sin(sqrt(x*x + y*y)) * exp(-0.1 * (x*x + y*y));
    }
};

#endif // PLOT3DDEMO_H