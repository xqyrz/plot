//
// Created by 25137 on 2026/10/25.
//
#include <iostream>
#include "cal/opencvcal.h"

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
    VisionApp w;
    w.show();
    w.resize(800,600);
    return a.exec();
}