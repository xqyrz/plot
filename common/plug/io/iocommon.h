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
    enum class  RT
    {
        RX,
        TX
    };
   class Frame{
   public:
        Config  info;//发送设备的信息
        QDateTime time;
        RT RT;
        QByteArray data;
    };
    typedef enum
    {
        OPEN_STATUS,
        CLOSE_STATUS,
        FAIL_STATUS
    }STATUS;
}
Q_DECLARE_METATYPE(IO::Frame)
#endif //IOCOMMON_H
