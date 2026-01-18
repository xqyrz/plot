//
// Created by 25137 on 26-1-11.
//

#ifndef TEST_H
#define TEST_H

#include <qobject.h>
#include "../io/iointerface.h"
#include <QDebug>
class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject* parent = nullptr)
        : QObject(parent) {}

    void setCallBack(std::function<void(const IO::Frame&)> cb)
    {
        t = std::move(cb);
    }

public slots:
    void tx_frame(const IO::Frame& frame)
    {
        if (t) {
            t(frame);
        }
    }

private:
    std::function<void(const IO::Frame&)> t;
};


#endif //TEST_H
