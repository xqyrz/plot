//
// Created by 25137 on 26-1-11.
//

#include "manage.h"
#include <QPluginLoader>
#include "viewmanage.h"
#include "signalmanage.h"
#include "ioappinterfacemanage.h"
#include "iointerfacemanage.h"
QString ManageBase::check(QString& var) const
{
    for (auto& plug : plugs)
    {
        QPluginLoader pluginLoader(plug);
        if (pluginLoader.metaData().value("className").toString() == var)
        {
            return plug;
        }
    }
    return {};
}
QObject* Manage::getObj(const int index)
{
    QObject* obj = nullptr;
    if (IOInterfaceManage::instance()->hasIndex(index))
    {
        obj = IOInterfaceManage::instance()->getObj(index);
    }
    else if (IOAPPInterfaceManage::instance()->hasIndex(index))
    {
        obj = IOAPPInterfaceManage::instance()->getObj(index);
    }
    else if (SignalManage::instance()->hasIndex(index))
    {
        obj = SignalManage::instance()->getObj(index);
    }
    else if (VIEWManage::instance()->hasIndex(index))
    {
        obj = VIEWManage::instance()->getObj(index);
    }
    else
    {
        qWarning() << "not find getObj index:" << index;
    }
    return obj;
}
InterfaceBase* Manage::getInterfaceBase(const int index)
{
    InterfaceBase* obj = nullptr;
    if (IOInterfaceManage::instance()->hasIndex(index))
    {
        obj = qobject_cast<IOInterface*>(IOInterfaceManage::instance()->getObj(index));
    }
    else if (IOAPPInterfaceManage::instance()->hasIndex(index))
    {
        obj = qobject_cast<IOAPPInterface*>(IOAPPInterfaceManage::instance()->getObj(index));
    }
    else if (SignalManage::instance()->hasIndex(index))
    {
        //obj =qobject_cast<SignalManage*>(SignalManage::instance()->getObj(index));
    }
    else if (VIEWManage::instance()->hasIndex(index))
    {
       // obj =qobject_cast<V*>(VIEWManage::instance()->getObj(index));
    }
    else
    {
        qWarning() << "not find getObj index:" << index;
    }
    return obj;
}
QObject* Manage::creatObj(const int index, QString type)
{
    QObject* obj = nullptr;
  //  qDebug()<<index->type()<<type<<index->caption()<<index->name();
    // switch (index->type())
    // {
    //
    // case BaseModel::IO_TYPE:obj     = IOInterfaceManage::instance()->creatObj(index, type);break;
    // case BaseModel::IOAPP_TYPE: obj = IOAPPInterfaceManage::instance()->creatObj(index, type);break;
    // case BaseModel::VIEW_TYPE:  obj = VIEWManage::instance()->creatObj(index, type);break;
    // case BaseModel::SIGNAL_TYPE:obj = SignalManage::instance()->creatObj(index, type);break;
    // case BaseModel::DEFAULT_TYPE:
    //     default: qWarning()<<"not find getObj index:"<<index <<"type:"<<index->type();
    // }
    return obj;
}
void Manage::showConfig(const int index)
{
   // auto obj = getObj(index);
   // qDebug()<<obj;
}
