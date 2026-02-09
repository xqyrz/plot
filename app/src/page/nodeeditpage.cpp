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
            //plugin->deleteLater();
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
    auto& model = scene->getGraphModel();
    auto allNodeIds = model.allNodeIds();

    for (auto& var : allNodeIds)
    {
        auto type = model.nodeData(var, NodeRole::Type).toString();
        if (VIEWManage::VIEW_ENUM_DATA.values().contains(type)) // 管理
        {
            VIEWManage::instance()->creatObj(var, type);
        }
        else if (!IOInterfaceManage::instance()->check(type).isEmpty())
        {
            IOInterfaceManage::instance()->creatObj(var, type);
        }
        else if (!IOAPPInterfaceManage::instance()->check(type).isEmpty())
        {
            IOAPPInterfaceManage::instance()->creatObj(var, type);
        }
        else if (!SignalManage::instance()->check(type).isEmpty())
        {
            SignalManage::instance()->creatObj(var, type);
        }
        else
        {
            qCritical() << "todo: not type nodeIds" << var << type;
        }
    }
    for (auto& var : allNodeIds)
    {
        auto cIds = model.allConnectionIds(var);

        for (auto& cid : cIds)
        {
            try
            {
                QObject* in_obj = Manage::getObj(cid.inNodeId);
                QObject* out_obj = Manage::getObj(cid.outNodeId);
               // qDebug() << "in:" << cid.inNodeId << in_obj << "out:" << cid.outNodeId << out_obj;

                if (!in_obj || !out_obj)
                {
                    throw std::runtime_error(QString("connection skipped because obj is null; inNodeId=%1 outNodeId=%2")
                                                 .arg(cid.inNodeId)
                                                 .arg(cid.outNodeId)
                                                 .toStdString());
                }

                auto* in_base = dynamic_cast<InterfaceBase*>(in_obj);
                auto* out_base = dynamic_cast<InterfaceBase*>(out_obj);
                if (!in_base || !out_base)
                {
                    throw std::runtime_error(
                        QString("%1: connection skipped because obj is not InterfaceBase; inNodeId=%2 outNodeId=%3")
                            .arg(in_base ? "out" : "in")
                            .arg(cid.inNodeId)
                            .arg(cid.outNodeId)
                            .toStdString());
                }

                const char* in_slot = in_base->getSlot(cid.inPortIndex);
                const char* out_signal = out_base->getSignal(cid.outPortIndex);
                if (!in_slot || !out_signal)
                {
                    throw std::runtime_error(
                        QString(
                            "%1: connection skipped because  is null; inNodeId=%2 inPort=%3 outNodeId=%4 outPort=%5")
                            .arg(in_slot ? "out signal" : "in slot")
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
                    throw std::runtime_error(
                        QString("QObject::connect failed; inNodeId: %1 inPort: %2 outNodeId: %3 outPort: %4")
                            .arg(cid.inNodeId)
                            .arg(in_slot)
                            .arg(cid.outNodeId)
                            .arg(out_signal)
                            .toStdString());
                }
                else
                {
                    qInfo()<<out_obj<<out_signal<<" <===connect==> "<<in_obj<<in_slot;
                }
            }
            catch (const std::exception& e)
            {
                qWarning() << "sceneLoaded:" << e.what();
            }
        }
    }
}
/**
 * 显示IO config
 *
 */
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
void NodeEditPage::showConfigDialog(InterfaceBase* obj)
{
    QDialog d(this);
    auto config = obj->showConfigDialog();
    QtTreePropertyBrowser editor(&d);
    QList<QtVariantProperty*> propertys;
    auto manager = new QtVariantPropertyManager(&d);
    for (auto & var:config)
    {

        QtVariantProperty* property;
        if (std::get<0>(var) == QVariant::StringList)
        {
             property = manager->addProperty(QtVariantPropertyManager::enumTypeId(),std::get<1>(var));
             //qDebug()<<std::get<2>(var);
             property->setAttribute(QLatin1String("enumNames"),std::get<2>(var));
             property->setValue(0);
        }
        else
        {
             property = manager->addProperty(std::get<0>(var),std::get<1>(var));
             property->setValue(std::get<2>(var));
        }
        editor.addProperty(property);
        propertys.append(property);
    }
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(&d);

    editor.setFactoryForManager(manager, variantFactory);
    editor.setPropertiesWithoutValueMarked(true);
    editor.setRootIsDecorated(false);
    QHBoxLayout layout(&d);
    layout.addWidget(&editor);

    d.exec();
    for (int i = 0;i<config.size();i++)
    {
        if (std::get<0>(config[i]) == QVariant::StringList)
        {
            auto index = propertys.at(i)->value().toInt();
            std::get<2>(config[i]) = propertys.at(i)->attributeValue("enumNames").toStringList().at(index);
        }
        else std::get<2>(config[i]) = propertys.at(i)->value();
    }
    obj->setConfigDialog(config);
    //obj->open();
}

NodeEditPage::NodeEditPage(QWidget* parent)
    :GraphicsView(parent)
    ,registry( registerDataModels())
    ,dataFlowGraphModel(new DataFlowGraphModel(registry))
    ,scene(new DataFlowGraphicsScene(*dataFlowGraphModel))
{
    connect(dataFlowGraphModel,&DataFlowGraphModel::configClicked,this,[this](int index)
    {
            //TODO
        if (auto obj =qobject_cast<IOInterface*>(Manage::getObj(index)))
        {
            qInfo()<<"configClicked "<<index<<obj;
            auto config =obj->getConfig();

            showConfigDialog(obj);
        }
        else  if (auto obj =qobject_cast<IOAPPInterface*>(Manage::getObj(index)))
        {
            qInfo()<<"IOAPPInterface configClicked "<<index<<obj;
             showConfigDialog(obj);
        }
    });
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
