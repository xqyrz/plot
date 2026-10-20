//
// Created by 25137 on 2026/10/10.
//

#include "manageinterface.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QtNodes/DataFlowGraphModel>
#include "../../../common/plug/io/iointerface.h"
#include "../../../common/plug/ioapp/ioappinterface.h"
#include "../../../common/plug/page/pagebase.h"
#include "page/node/signalinterface.h"

#include "manageinterface.h"


using namespace  QtNodes;

static PlugData dealPlug( QPluginLoader* pluginLoader)
{
    PlugData plugData;
    // 获取元数据（名称、版本、依赖）
    QJsonObject meta = pluginLoader->metaData();

    auto json = meta.value("MetaData").toObject();
    auto iid = meta.value("IID").toString();
    plugData.name = meta.value("className").toString();
    plugData.date = json["date"].toString();
    plugData.fileName = pluginLoader->fileName();


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
        return{};
    }
    auto obj =static_cast<InterfaceBase*>( pluginLoader->instance());
    if (obj)
    {
        plugData.in = obj->inputPorts();
        plugData.out = obj->outputPorts();

    }
    return plugData;
}




ManageInterface::ManageInterface(QObject* parent):
QObject(parent)

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


    m_registry =  _registerDataModels();
    dataFlowGraphModel = (new DataFlowGraphModel(m_registry));
    connect(dataFlowGraphModel,&DataFlowGraphModel::configClicked,this,[this](NodeDelegateModel* node)
    {
       emit configClicked((BaseModel*)node);
    });
}




ManageInterface* ManageInterface::instance(QObject* parent)
{
    static ManageInterface instance(parent);
    return &instance;
}
void ManageInterface::addPlug( QPluginLoader* pluginLoader)
{
    auto plugData = dealPlug(pluginLoader);

    if (plugs.contains(plugData))return;
    plugs.append(plugData);
}



std::shared_ptr<NodeDelegateModelRegistry> ManageInterface::_registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();

    for (auto var:BaseModel::inputTypeMap){
        SignalInterface signalInterface(BaseModel::inputTypeMap.key(var));
        auto inPort = INNodeData(var);
        QList<PLUG::InputType> in;
        for (int i = 0; i < 5; ++i)
        {
            in.append(BaseModel::inputTypeMap.key(var));
        }

        QList<PLUG::OutputType> out;
        auto key = BaseModel::inputTypeMap.key(var);
        out.append(BaseModel::inputTOoutput.value(key));
        ret->registerModel<BaseModel>(
        [name = inPort.type().name, in =in, out = out, nodeType=BaseModel::SIGNAL_TYPE]() {
            return std::make_unique<BaseModel>(name,nodeType, name, in, out);
        },
       PLUG::TypeStr(PLUG::Type::SIGNAL)
    );
    }

    for (auto  var :plugs) {
        auto nodeType = BaseModel::PLUG_TO_NODE_TYPE(var.type);  // 恢复类型映射
        // 用插件信息区分注册名，避免互相覆盖

        ret->registerModel<BaseModel>(
            [plugPath=var.fileName, name = var.name, in = var.in, out = var.out, nodeType]() {
                return std::make_unique<BaseModel>(plugPath,nodeType, name, in, out);
            },
           PLUG::TypeStr(var.type)
        );
    }

    return ret;
}