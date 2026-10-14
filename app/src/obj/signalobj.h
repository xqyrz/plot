//
// Created by 25137 on 26-1-10.
//

#ifndef SIGNALOBJ_H
#define SIGNALOBJ_H

#include <QMap>
#include <QObject>
#include "../../../common/plug/io/iointerface.h"
#include "../../../common/plug/ioapp/ioappinterface.h"
 namespace  SIGNALDATA
{
    typedef enum
    {
        IO_RX,
        APP_SIGNAL,
        APP_RX
    }SIGNALS_ENUM;
     static QMap<SIGNALS_ENUM,QString> SIGNALS_ENUM_DATA= {
         {IO_RX, "rx"},
        {APP_SIGNAL, "signal"},
         {APP_RX, "app_rx"}
     };
}
class SignalObj:public InterfaceBase{
Q_OBJECT
public:
    SignalObj(SIGNALDATA::SIGNALS_ENUM _type, QObject *parent = nullptr):InterfaceBase(parent),type(_type){};
      ~SignalObj() override = default;
signals:
     void sig_rx_frame(const PLUG::Frame&);
     void sig_hasSignal(const QList<PLUG::_SIGNALS>&);
     void sig_app_rx(const PLUG::Frame&);
 public slots:
     void slot_rx_frame(const PLUG::Frame&);
     void slot_hasSignal(const QList<PLUG::_SIGNALS>&);
     void slot_app_rx(const PLUG::Frame&);
private:
    QList<QObject*> in;
    QList<QObject*> out;
    SIGNALDATA::SIGNALS_ENUM type;
};


#endif //SIGNALOBJ_H
