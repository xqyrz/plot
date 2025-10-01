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
        QDateTime time;
        QByteArray data;
    }Frame;
    typedef struct {
      QString dev;//设备 ip
      QString ch;//通道 port

    }Config;
}
#endif //IOCOMMON_H
