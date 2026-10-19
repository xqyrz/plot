//
// Created by 25137 on 2026/10/19.
//

#include "plugloader.h"
#include <QMetaEnum>
#include "nodedata.h"
#include "signalinterface.h"
#include "nodemodel.h"
PlugLoader::PlugLoader(const QString& _fileName, QObject* parent) :
QPluginLoader(_fileName,parent)
{
    if (!fileName().contains(".dll"))
    {
        // 1. 枚举值 -> QString名字
        QMetaEnum metaEnum = QMetaEnum::fromType<QtNodes::NodeDataTypeEnum::InputType>();
        bool ok;
        int val = metaEnum.keyToValue(("IN_"+_fileName).toUtf8(), &ok);
        if(ok){
           m_interface = new SignalInterface(BaseModel::NODE_InputTYPE_TO_InputPLUG(
               static_cast<QtNodes::NodeDataTypeEnum::InputType>(val))
               ,this
               );
        }
    }
    else
    {

    }
}
PlugLoader::~PlugLoader()
{
    unload();
}
QObject* PlugLoader::P_interface()
{
    auto f = fileName();
    if (f.contains(".dll"))
    {
        if (!isLoaded())load();
        auto obj = this->instance();
        return obj;
    }
    return (QObject*) m_interface;
}
bool PlugLoader::P_load()
{
    if (fileName().contains(".dll"))
    {
        return QPluginLoader::load();
    }
    return true;
}
