//
// Created by 25137 on 26-1-10.
//

#include "interfacebase.h"
const char* InterfaceBase::getSignal(PLUG::InputType index) const
{
    switch (index)
    {
        case PLUG::InputType::IN_VIRTUAL_TX:return SIGNAL(signals_IN_IO_TX(const PLUG::Frame&));
        case PLUG::InputType::IN_IO_TX:return SIGNAL(signals_IN_IO_TX(const PLUG::Frame&));
        case PLUG::InputType::IN_IO_RX:return SIGNAL(signals_IN_IO_RX(const PLUG::Frame&));
        case PLUG::InputType::IN_APP_TX:return SIGNAL(signals_IN_APP_TX(const PLUG::Frame&));
        case PLUG::InputType::IN_APP_RX:return SIGNAL(signals_IN_APP_RX(const PLUG::Frame&));
        case PLUG::InputType::IN_APP_SIGNAL:return SIGNAL(signals_IN_APP_SIGNAL(const QList<PLUG::_SIGNALS>&));
    default:
        Q_ASSERT(1);
    }
    return nullptr;
}
const char* InterfaceBase::getSlot(PLUG::OutputType index) const
{
    switch (index)
    {
    case PLUG::OutputType::OUT_IO_TX:return SLOT(slots_OUT_IO_TX(const PLUG::Frame&));
    case PLUG::OutputType::OUT_IO_RX:return SLOT(slots_OUT_IO_RX(const PLUG::Frame&));
    case PLUG::OutputType::OUT_APP_TX:return SLOT(slots_OUT_APP_TX(const PLUG::Frame&));
    case PLUG::OutputType::OUT_APP_RX:return SLOT(slots_OUT_APP_RX(const PLUG::Frame&));
    case PLUG::OutputType::OUT_APP_SIGNAL:return SLOT(slots_OUT_APP_SIGNAL(const QList<PLUG::_SIGNALS>&));
    default:
        Q_ASSERT(1);
    }
    return nullptr;

}


void InterfaceBase::slots_OUT_IO_TX(const PLUG::Frame& frame)
{
    emit signals_IN_IO_RX(frame);
}
void InterfaceBase::slots_OUT_IO_RX(const PLUG::Frame& frame)
{
    emit signals_IN_IO_TX(frame);
}
void InterfaceBase::slots_OUT_APP_TX(const PLUG::Frame& frame)
{
    emit signals_IN_APP_RX(frame);
}
void InterfaceBase::slots_OUT_APP_RX(const PLUG::Frame& frame)
{
    emit signals_IN_APP_TX(frame);
}
void InterfaceBase::slots_OUT_APP_SIGNAL(const QList<PLUG::_SIGNALS>& _signals)
{
    emit signals_IN_APP_SIGNAL(_signals);
}
