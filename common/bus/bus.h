#ifndef BUS_H
#define BUS_H

#include <QList>
#include <QObject>
#include "../../plug/io/iocommon.h"
#include <QDebug>

class BUS:public QObject
{
    Q_OBJECT
public:
    static BUS* interface()
    {
       if (bus == nullptr) bus = new BUS(0);
        return bus;
    }
    // 分发数据给所有订阅者
     void readIO(const QList<IO::Frame>& frames) {
        emit readIO_sig(frames);
    }
signals:
    void readIO_sig(const QList<IO::Frame>&);
private:
    BUS(QObject* parent=nullptr):QObject(parent){};
    static BUS* bus;
};
#endif // BUS_H