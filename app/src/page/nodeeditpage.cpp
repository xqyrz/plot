//
// Created by 25137 on 25-12-16.
//

#include "nodeeditpage.h"
#include "node/nodemodel.h"
#include <QCoreApplication>
#include <QDir>
#include "../plug/io/iointerface.h"
#include "../plug/ioapp/ioappinterface.h"
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QPluginLoader>
#include <QTimer>
#include <QMutexLocker>
#include <QDir>
static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();
    auto creator = []() { return std::make_unique<IOModel>(IOModel::IO_TYPE,"IO"); };
     ret->registerModel<IOModel>(std::move(creator));
    auto creator_1 = []() { return std::make_unique<IOModel>(IOModel::IOAPP_TYPE,"IOAPP"); };
    ret->registerModel<IOModel>(std::move(creator_1));

    auto creator_2 = []() { return std::make_unique<IOModel>(IOModel::VIEW_TYPE,"VIEW_TYPE"); };
    ret->registerModel<IOModel>(std::move(creator_2));
    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();
    auto plugins =dir.absolutePath()+"/plugins";
    QCoreApplication::addLibraryPath(plugins);
    // qInfo() <<plugins<<"libraryPaths "<< QCoreApplication::libraryPaths();
    QDir path = QDir( plugins);
    foreach(QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
        qInfo() <<"........... "<<info.absoluteFilePath();
        QPluginLoader pluginLoader(info.absoluteFilePath());
        QObject* plugin = pluginLoader.instance();
        if (plugin)
        {
            // 获取元数据（名称、版本、依赖）

            QJsonObject meta = pluginLoader.metaData();
            //qDebug()<<meta;
            auto json = meta.value("MetaData").toObject();
            auto iid = meta.value("IID").toString();
            auto className = meta.value("className").toString();
            qInfo() << QString("**********  %1 %2:%3   **********").arg(info.baseName(),iid,className);
            //访问感兴趣的接口
            if (iid == IOInterface_Id)
            {
                if (className == "ATCPServer")
                {
                }
                else if (className == "ATCPClient") {
                }
                else if (className == "AUdp") {
                }
            }
            else if (iid == IOAPPInterface_Id)
            {
                if (className == "SelfIOAPP")
                {

                }
            }
        }
        else
        {
            qInfo() << pluginLoader.errorString();
        }
    }



    return ret;
}
NodeEditPage::NodeEditPage(QWidget* parent)
    :GraphicsView(parent)
    ,registry( registerDataModels())
    ,dataFlowGraphModel(new DataFlowGraphModel(registry))
    ,scene(new DataFlowGraphicsScene(*dataFlowGraphModel))
{
    ConnectionStyle::setConnectionStyle(
    R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");
  this->setScene(scene);

}
