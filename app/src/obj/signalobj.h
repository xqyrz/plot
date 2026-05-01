//
// Created by 25137 on 26-1-10.
//

#ifndef SIGNALOBJ_H
#define SIGNALOBJ_H

#include <QMap>
#include <QObject>
#include "iointerface.h"
#include "../ioapp/ioappinterface.h"
 namespace  SIGNALDATA
{
    typedef enum
    {
        IO_RX,
        APP_SIGNAL
    }SIGNALS_ENUM;
     static QMap<SIGNALS_ENUM,QString> SIGNALS_ENUM_DATA= {
         {IO_RX, "rx"},
        {APP_SIGNAL, "signal"}
     };
}
class SignalObj:public QObject,public InterfaceBase{
Q_OBJECT
public:
    SignalObj(SIGNALDATA::SIGNALS_ENUM _type, QObject *parent = nullptr):QObject(parent),type(_type){};
      ~SignalObj() override = default;
     const char* getSignal(int index) const override;
     const char* getSlot(int index) const override;
signals:
     void sig_rx_frame(const IO::Frame&);
     void sig_hasSignal(const QList<IOAPP::SIGNALS>&);

 public slots:
     void slot_rx_frame(const IO::Frame&);
     void slot_hasSignal(const QList<IOAPP::SIGNALS>&);
private:
    QList<QObject*> in;
    QList<QObject*> out;
    SIGNALDATA::SIGNALS_ENUM type;
};


#endif //SIGNALOBJ_H
