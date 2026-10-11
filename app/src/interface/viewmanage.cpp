//
// Created by 25137 on 26-1-2.
//

#include "viewmanage.h"
#include "../../../plug/page/iowpage/ioview.h"
#include "plotview.h"
#include <QDebug>
using TypeEnum=QtNodes::NodeDataTypeEnum;
 VIEWManage* VIEWManage::m_viewManage =nullptr;
VIEWManage* VIEWManage::instance(QObject* parent)
{
    if (m_viewManage == nullptr)
    {
        m_viewManage = new VIEWManage(parent);
    }
    return m_viewManage;
}
bool VIEWManage::hasType(const QString& type)
{
    return false;
}
BaseModel VIEWManage::creatType(const QString& type)
{
    return {};
}
QString VIEWManage::check(QString& var) const
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
QObject* VIEWManage::creatObj(const int  index, QString type)
{
    if (!objs.contains(index)){
        QPluginLoader pluginLoader(check(type));
        auto obj = (pluginLoader.instance());
        objs.insert(index, obj);
    }
    return objs.value(index);
}
bool VIEWManage::hasIndex(const int  index) const
{
    return objs.contains(index);
}
VIEWManage::VIEWManage(QObject* parent):QObject(parent)
{

}
