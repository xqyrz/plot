//
// Created by 25137 on 2026/9/27.
//
#include "axfpage.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AxfPage w;
    w.resize(800, 600);
    w.show();

    return a.exec();
}
