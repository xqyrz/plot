//
// Created by 25137 on 26-2-10.
//


#include <QtWidgets/QApplication>
#include <iowpage.h>
int main(int argc, char *argv[]) {
    // 1. 全局缩放使能
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // 2. 适配非整数倍缩放
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication a(argc, argv);
IOWPage w;
    w.resize(800,600);
    w.show();

    return a.exec();
}
