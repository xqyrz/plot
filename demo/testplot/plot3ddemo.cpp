#include "plot3ddemo.h"
#include <QToolBar>
#include <QColor>

Plot3DDemo::Plot3DDemo(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Qwt3D Plot3D 演示程序");
    setMinimumSize(800, 600);

    // 初始化 3D 绘图
    initPlot3D();
}

void Plot3DDemo::initPlot3D()
{
    // 1. 创建 Plot3D 对象
    m_plot3d = new Qwt3D::Plot3D(this);
    setCentralWidget(m_plot3d);

    // 2. 创建自定义 3D 函数
    My3DFunction* func = new My3DFunction(m_plot3d);

    // 3. 设置函数采样范围（x, y 轴范围）
    func->setDomain(-5, 5, -5, 5);
    // 设置采样精度（数值越高曲面越平滑）
    func->setResolution(80, 80);

    // 4. 绑定函数到 3D 绘图
    func->assign();

    // ===================== 样式配置 =====================
    // 设置标题
    m_plot3d->setTitle("Qwt3D 3D 曲面演示");
    m_plot3d->setTitleColor(QColor(255, 0, 0));

    // 设置坐标轴标签
    m_plot3d->setXAxisLabel("X 轴");
    m_plot3d->setYAxisLabel("Y 轴");
    m_plot3d->setZAxisLabel("Z 轴");

    // 开启网格
    m_plot3d->setMesh(true);
    // 开启颜色映射（根据 Z 值自动上色）
    m_plot3d->setColorLegend(true);

    // 设置视角（初始角度）
    m_plot3d->setRotation(30, 0, 15);

    // 开启鼠标交互（默认已开启，显式声明）
    // 左键旋转 / 滚轮缩放 / 右键平移
    m_plot3d->setMouseTracking(true);
}