//
// Created by 25137 on 2026/10/25.
//
#include <iostream>
#include "cal/opencvcal.h"
#include <QLoggingCategory>
int test()
{
    // 字符串版本
    std::cout << "CV_VERSION: " << CV_VERSION << "\n";
    OpencvCal cal;

    // 6. 显示与保存
    cv::imshow("currImage", *cal.currImage());

    cv::Mat out;
    auto size = cal.currImage()->size();

    auto M = cal.move(64,0,size);
    cal.Affine_Transformation(M, out);
    cv::imshow("currImage->moveX 64", out);
    cal.Affine_Transformation(cal.move(0,64,size,M), out);
    cv::imshow("currImage->moveX 64->moveY 64", out);

     M = cal.rotate(10,size);
    cal.Affine_Transformation(M, out);
    cv::imshow("currImage->rotate 10", out);

     M = cal.scale(0.5,2,size);
    cal.Affine_Transformation(M, out);
    cv::imshow("currImage->scale 0.9,0.8", out);

    cv::waitKey(0);
    return 0;
}

void intlog()
{
    qSetMessagePattern(
    // 基础信息
    "%{time process} "
    "[%{threadid}] "

#ifdef QT_DEBUG
    // Debug：绿色
    "%{if-debug}\033[32m%{endif}"

    // Info：白色
    "%{if-info}\033[37m%{endif}"

    // Warning：黄色
    "%{if-warning}\033[33m%{endif}"

    // Critical：红色
    "%{if-critical}\033[31m%{endif}"

    // Fatal：红色背景加粗
    "%{if-fatal}\033[41;1m%{endif}"
#endif

    // 日志级别
    "%{if-debug}D%{endif}"
    "%{if-info}I%{endif}"
    "%{if-warning}W%{endif}"
    "%{if-critical}E%{endif}"
    "%{if-fatal}F%{endif}"

    // 日志分类
    "%{if-category} [%{category}]%{endif}"

#ifdef QT_DEBUG
    // 文件、行号、函数
    " [%{function}:%{line}]"
#endif

    // 日志内容
    " %{message}"

#ifdef QT_DEBUG
    // 颜色重置
    "\033[0m"
#endif
);
}
#include <QtWidgets/QApplication>
#include "visionapp.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    // 1. 全局缩放使能
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // 2. 适配非整数倍缩放
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);
    intlog();
    VisionApp w;
    w.show();
    w.resize(800,600);
    return a.exec();
}