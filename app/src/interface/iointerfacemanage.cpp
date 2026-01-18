//
// Created by 25137 on 26-1-1.
//

#include "iointerfacemanage.h"
#include <QGlobalStatic>
IOInterfaceManage* IOInterfaceManage::m_iOInterfaceManage = nullptr;


QString IOInterfaceManage::check(QString& var) const
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
bool IOInterfaceManage::creatObj(int index, QString type)
{
    QPluginLoader pluginLoader(check(type));
    objs.insert(index, (pluginLoader.instance()));
    return !objs.value(index);
}
QObject* IOInterfaceManage::getObj(int index) const
{
    return objs.value(index);
}
bool IOInterfaceManage::hasIndex(int index) const
{
   return objs.contains(index);
}
IOInterfaceManage::IOInterfaceManage(QObject *parent)
    : QObject(parent)
{

}

IOInterfaceManage *IOInterfaceManage::instance()
{
    if (m_iOInterfaceManage == nullptr)
    {
        m_iOInterfaceManage = new IOInterfaceManage();
    }
    return m_iOInterfaceManage;
}