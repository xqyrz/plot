//
// Created by 25137 on 26-2-10.
//


#include <QtWidgets/QApplication>
#include "iopage.h"
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    IOPage w;
    w.resize(400,300);
    w.show();

    return a.exec();
}
