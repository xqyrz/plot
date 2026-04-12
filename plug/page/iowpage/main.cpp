//
// Created by 25137 on 26-2-10.
//


#include <QtWidgets/QApplication>
#include <iowpage.h>
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    IOWPage w;
    w.resize(800,600);
    w.show();

    return a.exec();
}
