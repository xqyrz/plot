//
// Created by 25137 on 25-12-16.
//

#include "nodeeditpage.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QMutexLocker>
#include <QPluginLoader>
#include <QStandardPaths>
#include <QTimer>
#include "../plug/io/iointerface.h"
#include "../plug/ioapp/ioappinterface.h"
#include "node/nodemodel.h"
static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();

    auto creator_2 = []()
    {
        return std::make_unique<ViewModel>("VIEW_TYPE");
    };
    ret->registerModel<ViewModel>(std::move(creator_2));
    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();
    auto plugins =dir.absolutePath()+"/plugins";
    QCoreApplication::addLibraryPath(plugins);
    // qInfo() <<plugins<<"libraryPaths "<< QCoreApplication::libraryPaths();
    QDir path = QDir( plugins);
    foreach(QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
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
                auto creator = [className]() { return std::make_unique<IOModel>(className); };
                ret->registerModel<IOModel>(std::move(creator),"IO");
            }
            else if (iid == IOAPPInterface_Id)
            {
                auto creator = [className]() { return std::make_unique<IOAPPModel>(className); };
                ret->registerModel<IOAPPModel>(std::move(creator),"IOAPP");
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
    QTimer::singleShot(1,[this](){
        try
        {
            this->scene->load(this->scene->getDefaultConfigPath());
        }
        catch (const std::logic_error& e) {
            QMessageBox::warning(this,"警告","节点配置文件加载失败："+QString(e.what()));
           qWarning() << e.what();
        }
    });
}
