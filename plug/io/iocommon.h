//
// Created by 25137 on 25-10-1.
//

#ifndef IOCOMMON_H
#define IOCOMMON_H
#include <QObject>
#include <QDateTime>
//#include <chrono>
//using TimePoint = std::chrono::system_clock::time_point;
namespace IO{
    typedef struct {
        QString dev;//设备 ip
        QString ch;//通道 port
        QString own_dev; //自己
        QString own_ch;
    }Config;
    typedef struct {
        Config  info;//发送设备的信息
        QDateTime time;
        QByteArray data;
    }Frame;

}
#endif //IOCOMMON_H
