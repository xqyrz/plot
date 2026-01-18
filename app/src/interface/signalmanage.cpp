//
// Created by 25137 on 26-1-10.
//

#include "signalmanage.h"

#include <QSharedPointer>
using namespace SIGNALDATA;
SignalManage* SignalManage::m_SignalManage =nullptr;
SignalManage* SignalManage::instance(QObject* parent)
{
    if (m_SignalManage == nullptr)
    {
        m_SignalManage = new SignalManage(parent);
    }
    return m_SignalManage;
}
QString SignalManage::check(QString& var) const
{
    if (SIGNALS_ENUM_DATA.values().contains(var))
    {
        return var;
    }
    else return {};
}
bool SignalManage::creatObj(int index, QString type)
{
    if (!SIGNALS_ENUM_DATA.values().contains(type))
    {
        return false;
    }
    objs.insert(index, new SignalObj(SIGNALS_ENUM_DATA.key(type), this));
    return true;
}
bool SignalManage::addId(uint outNodeId, uint outPortIndex, uint inNodeId, uint inPortIndex)
{
    ids.append(std::tuple<uint,uint,uint,uint>(outNodeId,outPortIndex,inNodeId,inPortIndex));
    return true;
}
