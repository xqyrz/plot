//
// Created by 25137 on 26-1-1.
//

#include "ioappinterfacemanage.h"
#include <QPluginLoader>

#include "obj/signalobj.h"
#include "page/node/nodemodel.h"
IOAPPInterfaceManage* IOAPPInterfaceManage::m_iOAPPInterfaceManage = nullptr;



QObject* IOAPPInterfaceManage::creatObj(const int  index, QString type)
{
    QPluginLoader pluginLoader(check(type));
    objs.insert(index, ((pluginLoader.instance())));
    return objs.value(index);
}
bool IOAPPInterfaceManage::hasIndex(const int  index) const { return objs.contains(index); }
IOAPPInterfaceManage::IOAPPInterfaceManage(QObject *parent)
    : QObject(parent)
{

}

IOAPPInterfaceManage* IOAPPInterfaceManage::instance()
{
    if (m_iOAPPInterfaceManage == nullptr)
    {
        m_iOAPPInterfaceManage = new IOAPPInterfaceManage();
    }
    return m_iOAPPInterfaceManage;
}
