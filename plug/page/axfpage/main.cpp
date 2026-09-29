//
// Created by 25137 on 2026/9/27.
//
#include <QApplication>
#include "axfpage.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AxfPage w;
    w.resize(800, 600);
    w.show();

    return a.exec();
}
