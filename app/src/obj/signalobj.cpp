//
// Created by 25137 on 26-1-10.
//

#include "signalobj.h"
using namespace SIGNALDATA;
const char* SignalObj::getSignal(int index) const
{
    switch (type)
    {
        case   IO_RX:return SIGNAL(_rx_frame(const IO::Frame&));
        case APP_SIGNAL:return SIGNAL(_hasSignal(const QList<IOAPP::SIGNALS>&));
        default:return nullptr;
    }
}
const char* SignalObj::getSlot(int index) const
{
    switch (type){
    case   IO_RX:return SLOT(rx_frame(const IO::Frame&));
    case APP_SIGNAL:return SLOT(hasSignal(const QList<IOAPP::SIGNALS>&));
    default:return nullptr;
}
}
void SignalObj::rx_frame(const IO::Frame& frame)
{
    // qInfo()<<frame.data;
    emit _rx_frame(frame);
}
void SignalObj::hasSignal(const QList<IOAPP::SIGNALS>& _signals)
{
   // qInfo()<<_signals.size();
    emit _hasSignal(_signals);
}
