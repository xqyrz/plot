//
// Created by 25137 on 26-1-10.
//

#include "signalobj.h"
using namespace SIGNALDATA;
const char* SignalObj::getSignal(int index) const
{
    switch (type)
    {
        case   IO_RX:return SIGNAL(sig_rx_frame(const IO::Frame&));
        case APP_SIGNAL:return SIGNAL(sig_hasSignal(const QList<IOAPP::SIGNALS>&));
        default:return nullptr;
    }
}
const char* SignalObj::getSlot(int index) const
{
    switch (type){
    case   IO_RX:return SLOT(slot_rx_frame(const IO::Frame&));
    case APP_SIGNAL:return SLOT(slot_hasSignal(const QList<IOAPP::SIGNALS>&));
    default:return nullptr;
}
}

void SignalObj::slot_rx_frame(const IO::Frame& frame)
{
    QList< IO::Frame> f;
    f.append(frame);
    // qInfo()<<frame.data;
    emit sig_rx_frame(frame);
}
void SignalObj::slot_hasSignal(const QList<IOAPP::SIGNALS>& _signals)
{
   // qInfo()<<_signals.size();
    emit sig_hasSignal(_signals);
}
