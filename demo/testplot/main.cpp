#include "plot3ddemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Plot3DDemo w;
    w.show();
    return a.exec();
}