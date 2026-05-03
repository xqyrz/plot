//
// Created by 25137 on 26-1-2.
//

#include "viewmanage.h"
#include "../../../plug/page/iowpage/ioview.h"
#include "plotview.h"
#include <QDebug>
using TypeEnum=QtNodes::NodeDataTypeEnum;
QMap<VIEWManage::VIEW_ENUM, BaseModel> VIEWManage::VIEW_ENUM_DATA = {
    {VIEWManage::PLOT_VIEW, BaseModel(BaseModel::VIEW_TYPE
        , "PlotView"
        ,QList<QtNodes::NodeDataTypeEnum::InputType>{TypeEnum::IN_APP_RX,TypeEnum::IN_APP_SIGNAL}
        ,QList<QtNodes::NodeDataTypeEnum::OutputType> {TypeEnum::OUT_APP_TX}
        )},
{VIEWManage::IO_VIEW, BaseModel(BaseModel::VIEW_TYPE
    , "IOWPage"
    ,QList<QtNodes::NodeDataTypeEnum::InputType>{TypeEnum::IN_APP_RX}
    ,QList<QtNodes::NodeDataTypeEnum::OutputType> {TypeEnum::OUT_APP_TX}
    )},
};
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
    for (auto& var : VIEW_ENUM_DATA)
    {
        if (var.name() == type)
        {
            return true;
        }
    }

    return false;
}
BaseModel VIEWManage::creatType(const QString& type)
{
    for (auto& var : VIEW_ENUM_DATA)
    {
        if (var.name() == type)
        {
           return var;
        }
    }
    qWarning()<<"creatType fail"<<type;
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
