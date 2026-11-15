//
// Created by 25137 on 2026/9/27.
//
#include <QApplication>
#include <iostream>
#include "plotview.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PlotView w;
    w.onlyPlot(true);
    w.setZero(0);
    QList<PLUG::_SIGNALS> d;
    PLUG::_SIGNALS s;
    s.name ="value";
    for (int i = 0; i < 4095; ++i)
    {
        s.time = i;
        s.value = i;
       d.append(s);
    }
    w._addSignalData(d);
    w.ui()->resize(800, 600);
    w.ui()->show();

    return a.exec();
}
