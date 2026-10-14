//
// Created by 25137 on 26-1-10.
//

#include "signalobj.h"
using namespace SIGNALDATA;


void SignalObj::slot_rx_frame(const INC::Frame& frame)
{
    QList< INC::Frame> f;
    f.append(frame);
    // qInfo()<<frame.data;
    emit sig_rx_frame(frame);
}
void SignalObj::slot_hasSignal(const QList<INC::_SIGNALS>& _signals)
{
    // qInfo()<<_signals.size();
    emit sig_hasSignal(_signals);
}
void SignalObj::slot_app_rx(const INC::Frame& frame)
{
    emit sig_app_rx(frame);
}
