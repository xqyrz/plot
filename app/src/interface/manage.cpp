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
QObject* Manage::getObj(int index)
{
    QObject* obj=nullptr;
    if ( IOInterfaceManage::instance()->hasIndex(index))
    {
        obj = IOInterfaceManage::instance()->getObj(index);
    }
    else if (IOAPPInterfaceManage::instance()->hasIndex(index))
    {
        obj = IOAPPInterfaceManage::instance()->getObj(index);
    }
    else if (SignalManage::instance()->hasIndex(index))
    {
        obj =SignalManage::instance()->getObj(index);
    }
    else if (VIEWManage::instance()->hasIndex(index))
    {
        obj =VIEWManage::instance()->getObj(index);
    }

    return obj;
}
