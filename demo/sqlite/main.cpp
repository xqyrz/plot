#include <QCoreApplication>
#include "dbm.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    auto dbm = DBM::instance();
    QByteArray d(61,61);
    QString time("time");
    QString channel("channel");
    QString frame_id("frame_id");
    QString period("period");
    QString frame_cout("frame_cout");
    QString dir("dir");
    dbm->addFrame(time,channel,frame_id,period,frame_cout,dir,d);
    dbm->exportMemoryDb("test123.db");
    a.exec();
    return 0;
}