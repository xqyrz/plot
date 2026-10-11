//
// Created by 25137 on 2026/10/10.
//

#include "manageinterface.h"
#include <QCoreApplication>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>
#include "iointerfacemanage.h"
#include "ioappinterfacemanage.h"
#include "viewmanage.h"
#include "../plug/io/iointerface.h"
#include "../plug/ioapp/ioappinterface.h"
#include "../plug/page/pagebase.h"
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
            //    qInfo() << QString("load:[%1]  %2 %3:%4  ").arg(date,info.baseName(), iid, className);
            // 访问感兴趣的接口
            if (iid == IOInterface_Id)
            {

                IOInterfaceManage::instance()->addPlug(info.absoluteFilePath());
            }
            else if (iid == IOAPPInterface_Id)
            {

                IOAPPInterfaceManage::instance()->addPlug(info.absoluteFilePath());
            }
            else if (iid == PageBase_Id)
            {
                pluginLoader.instance();
                VIEWManage::instance()->addPlug(info.absoluteFilePath());
                pluginLoader.unload();
            }
            else
            {
                qWarning() <<"not load plugin"<<info.absoluteFilePath();
            }
            //plugin->deleteLater();
        }
        else
        {
            qWarning() <<info.absoluteFilePath()<< pluginLoader.errorString();
        }
    }

}
