//
// Created by 25137 on 25-10-1.
//

#ifndef IOCOMMON_H
#define IOCOMMON_H
#include <QDateTime>
#include <QtCore/qglobal.h>

#if defined(P_LIBRARY)
#  define P_EXPORT Q_DECL_EXPORT
#else
#  define P_EXPORT Q_DECL_IMPORT
#endif
namespace IO{
    typedef struct {
        QString dev;//设备 ip
        QString ch;//通道
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
