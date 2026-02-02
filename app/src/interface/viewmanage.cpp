//
// Created by 25137 on 26-1-2.
//

#include "viewmanage.h"
#include "plotview.h"
QMap<VIEWManage::VIEW_ENUM, QString> VIEWManage::VIEW_ENUM_DATA = {{VIEWManage::PLOT_VIEW, "Plot"}};
VIEWManage* VIEWManage::m_viewManage =nullptr;
VIEWManage* VIEWManage::instance(QObject* parent)
{
    if (m_viewManage == nullptr)
    {
        m_viewManage = new VIEWManage(parent);
    }
    return m_viewManage;
}
QString VIEWManage::check(QString& var) const
{
    return var;
}
QObject* VIEWManage::creatObj(const int  index, QString type)
{
    auto view_index = VIEW_ENUM_DATA.key(type);
    switch (view_index)
    {
    case PLOT_VIEW:
        objs.insert(index, PlotView::instance());
        return objs.value(index);
    default:
        return nullptr;
    }
}
bool VIEWManage::hasIndex(const int  index) const
{
    return objs.contains(index);
}
VIEWManage::VIEWManage(QObject* parent):QObject(parent)
{

}
