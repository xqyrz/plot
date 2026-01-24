//
// Created by 25137 on 25-12-16.
//

#include "nodeeditpage.h"
#include <QDateTime>
#include <QDebug>

#include <stdexcept>


#include "../plug/io/iointerface.h"
#include "../plug/ioapp/ioappinterface.h"
#include "interface/ioappinterfacemanage.h"
#include "interface/iointerfacemanage.h"
#include "interface/viewmanage.h"
#include "interface/signalmanage.h"
#include "interface/manage.h"
#include "node/nodemodel.h"
#include "plotview.h"
std::shared_ptr<NodeDelegateModelRegistry> NodeEditPage::registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();

    ret->registerModel<ViewModel>(std::move(
        []() { return std::make_unique<ViewModel>(VIEWManage::VIEW_ENUM_DATA.value(VIEWManage::PLOT_VIEW)); }));

    ret->registerModel<AppSignalModel>(std::move([]() { return std::make_unique<AppSignalModel>(
       SIGNALDATA::SIGNALS_ENUM_DATA.value(SIGNALDATA::APP_SIGNAL)
        ); }),
                                       "MANAGE");

    ret->registerModel<AppRxModel>(std::move(
        []() { return std::make_unique<AppRxModel>(
        SIGNALDATA::SIGNALS_ENUM_DATA.value(SIGNALDATA::IO_RX)
            ); })
        , "MANAGE");

    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();
    auto plugins = dir.absolutePath() + "/plugins";
    QCoreApplication::addLibraryPath(plugins);
    // qInfo() <<plugins<<"libraryPaths "<< QCoreApplication::libraryPaths();
    QDir path = QDir(plugins);
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
        QPluginLoader pluginLoader(info.absoluteFilePath());
        if (auto plugin = pluginLoader.instance())
        {
            // 获取元数据（名称、版本、依赖）

            QJsonObject meta = pluginLoader.metaData();
            // qDebug()<<meta;
            auto json = meta.value("MetaData").toObject();
            auto iid = meta.value("IID").toString();
            auto className = meta.value("className").toString();
            qInfo() << QString("**********  %1 %2:%3   **********").arg(info.baseName(), iid, className);
            // 访问感兴趣的接口
            if (iid == IOInterface_Id)
            {
                IOInterfaceManage::instance()->addPlug(info.absoluteFilePath());
                auto creator = [className]() { return std::make_unique<IOModel>(className); };
                ret->registerModel<IOModel>(std::move(creator), "IO");
            }
            else if (iid == IOAPPInterface_Id)
            {
                IOAPPInterfaceManage::instance()->addPlug(info.absoluteFilePath());
                auto creator = [className]() { return std::make_unique<IOAPPModel>(className); };
                ret->registerModel<IOAPPModel>(std::move(creator), "IOAPP");
            }
            plugin->deleteLater();
        }
        else
        {
            qInfo() << pluginLoader.errorString();
        }
    }


    return ret;
}
void dumpMeta(const QObject* obj)
{
    const QMetaObject* mo = obj->metaObject();

    qDebug() << "Class:" << mo->className();
    qDebug() << "---- Signals ----";

    for (int i = mo->methodOffset(); i < mo->methodCount(); ++i)
    {
        QMetaMethod m = mo->method(i);
        if (m.methodType() == QMetaMethod::Signal)
        {
            qDebug() << m.methodSignature();
        }
    }

    qDebug() << "---- Slots ----";

    for (int i = mo->methodOffset(); i < mo->methodCount(); ++i)
    {
        QMetaMethod m = mo->method(i);
        if (m.methodType() == QMetaMethod::Slot)
        {
            qDebug() << m.methodSignature();
        }
    }
}

void NodeEditPage::_sceneLoaded()
{
    auto & model = scene->getGraphModel();
    auto allNodeIds = model.allNodeIds();
    for (auto & var:allNodeIds)
    {
    auto cIds =  model.allConnectionIds(var);

     for (auto & cid: cIds)
     {
         try
         {
             QObject* in_obj=Manage::getObj(model.delegateModel<BaseModel>(cid.inNodeId));
             QObject* out_obj=Manage::getObj(model.delegateModel<BaseModel>(cid.outNodeId));
             qDebug()<<"in:"<<cid.inNodeId<<in_obj<<"out:"<<cid.outNodeId<<out_obj;

             if (!in_obj || !out_obj)
             {
                 throw std::runtime_error(QString("connection skipped because obj is null; inNodeId=%1 outNodeId=%2")
                                              .arg(cid.inNodeId)
                                              .arg(cid.outNodeId)
                                              .toStdString());
             }

             auto *in_base = dynamic_cast<InterfaceBase*>(in_obj);
             auto *out_base = dynamic_cast<InterfaceBase*>(out_obj);
             if (!in_base || !out_base)
             {
                 throw std::runtime_error(QString("%1: connection skipped because obj is not InterfaceBase; inNodeId=%2 outNodeId=%3")
                     .arg(in_base?"out":"in")
                                              .arg(cid.inNodeId)
                                              .arg(cid.outNodeId)
                                              .toStdString());
             }

             const char* in_slot = in_base->getSlot(cid.inPortIndex);
             const char* out_signal = out_base->getSignal(cid.outPortIndex);
             if (!in_slot || !out_signal)
             {
                 throw std::runtime_error(QString("%1: connection skipped because  is null; inNodeId=%2 inPort=%3 outNodeId=%4 outPort=%5")
                                              .arg(in_slot?"out signal":"in slot")
                                              .arg(cid.inNodeId)
                                              .arg(cid.inPortIndex)
                                              .arg(cid.outNodeId)
                                              .arg(cid.outPortIndex)
                                              .toStdString());
             }

             const bool ok = QObject::connect(out_obj, out_signal, in_obj, in_slot);
             if (!ok)
             {
                 dumpMeta(in_obj);
                 dumpMeta(out_obj);
                 throw std::runtime_error(QString("QObject::connect failed; inNodeId: %1 inPort: %2 outNodeId: %3 outPort: %4")
                                              .arg(cid.inNodeId)
                                              .arg(in_slot)
                                              .arg(cid.outNodeId)
                                              .arg(out_signal)
                                              .toStdString());
             }
         }
         catch (const std::exception& e)
         {
             qWarning() << "sceneLoaded:" << e.what();
         }
     }

    }


}
NodeEditPage::NodeEditPage(QWidget* parent)
    :GraphicsView(parent)
    ,registry( registerDataModels())
    ,dataFlowGraphModel(new DataFlowGraphModel(registry))
    ,scene(new DataFlowGraphicsScene(*dataFlowGraphModel))
{
    // SignalObj d(SIGNALDATA::IO_RX);
    // SelfIOAPP b(nullptr);
    // connect(&b,&SelfIOAPP::hasSignal,&d,&SignalObj::hasSignal);
    ConnectionStyle::setConnectionStyle(
    R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");
  this->setScene(scene);



    connect(scene,&DataFlowGraphicsScene::sceneLoaded, this,&NodeEditPage::_sceneLoaded);

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
