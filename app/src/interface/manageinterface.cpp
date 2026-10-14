//
// Created by 25137 on 2026/10/10.
//

#include "manageinterface.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include "../../../common/plug/io/iointerface.h"
#include "../../../common/plug/ioapp/ioappinterface.h"
#include "../../../common/plug/page/pagebase.h"
#include "manageinterface.h"
ManageInterface* ManageInterface::instance(QObject* parent)
{
    static ManageInterface instance(parent);
    return &instance;
}
void ManageInterface::addPlug( QPluginLoader* pluginLoader)
{
    PlugData plugData;
    // 获取元数据（名称、版本、依赖）
    QJsonObject meta = pluginLoader->metaData();

    auto json = meta.value("MetaData").toObject();
    auto iid = meta.value("IID").toString();
    plugData.name = meta.value("className").toString();
    plugData.date = json["date"].toString();
    plugData.fileName = pluginLoader->fileName();
    if (plugs.contains(plugData))return;

    if (iid == IOInterface_Id)
    {

        plugData.type = PLUG::Type::IO;
    }
    else if (iid == IOAPPInterface_Id)
    {

        plugData.type = PLUG::Type::IOAPP;
    }
    else if (iid == PageBase_Id)
    {
        plugData.type = PLUG::Type::VIEW;
    }
    else
    {
        qWarning() <<"not load plugin"<<pluginLoader->fileName();
        return;
    }
    auto obj =static_cast<InterfaceBase*>( pluginLoader->instance());
    if (obj)
    {
        plugData.in = obj->inputPorts();
        plugData.out = obj->outputPorts();
        plugs.append(plugData);
    }
}
ManageInterface::ManageInterface(QObject* parent):QObject(parent)
{

    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();
    auto plugins = dir.absolutePath() + "/plugins";
    QCoreApplication::addLibraryPath(plugins);
    // qInfo() <<plugins<<"libraryPaths "<< QCoreApplication::libraryPaths();
    QDir path = QDir(plugins);
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
        QPluginLoader pluginLoader(info.absoluteFilePath());
        if (pluginLoader.load())
        {
            // 获取元数据（名称、版本、依赖）
            QJsonObject meta = pluginLoader.metaData();
#ifdef QT_DEBUG
            if (!meta.value("debug").toBool())continue;
#else
            if (meta.value("debug").toBool())continue;
#endif
            auto json = meta.value("MetaData").toObject();
            auto iid = meta.value("IID").toString();
            auto className = meta.value("className").toString();
            auto date = json["date"].toString();
            qInfo() << QString("load:[%1]  %2 %3:%4  ").arg(date,info.baseName(), iid, className);
            // 访问感兴趣的接口
            addPlug(&pluginLoader);
        }
        else
        {
            qWarning() <<info.absoluteFilePath()<< pluginLoader.errorString();
        }
    }

}
