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
QObject* SignalManage::creatObj(const BaseModel*  index, QString type)
{
    if (!SIGNALS_ENUM_DATA.values().contains(type))
    {
        return nullptr;
    }
    auto obj =  new SignalObj(SIGNALS_ENUM_DATA.key(type), this);
     objs.insert(index,obj);
    return obj;
}
bool SignalManage::addId(uint outNodeId, uint outPortIndex, uint inNodeId, uint inPortIndex)
{
    ids.append(std::tuple<uint,uint,uint,uint>(outNodeId,outPortIndex,inNodeId,inPortIndex));
    return true;
}
