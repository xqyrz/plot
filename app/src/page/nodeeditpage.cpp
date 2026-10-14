//
// Created by 25137 on 25-12-16.
//

#include "nodeeditpage.h"
#include <QDateTime>
#include <QDebug>

#include <stdexcept>


#include "../../../common/plug/io/iointerface.h"
#include "../../../common/plug/ioapp/ioappinterface.h"
#include "../../../common/plug/page/pagebase.h"
#include "interface/manageinterface.h"
#include "node/nodemodel.h"
#include "plotview.h"
std::shared_ptr<NodeDelegateModelRegistry> NodeEditPage::_registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();
    for (auto  var : ManageInterface::instance()->getPlugs()) {
        auto nodeType = BaseModel::PLUG_TO_NODE_TYPE(var.type);  // 恢复类型映射
        // 用插件信息区分注册名，避免互相覆盖

        ret->registerModel<BaseModel>(
            [name = var.name, in = var.in, out = var.out, nodeType]() {
                qDebug()<<"in"<<in.size()<<"out"<<out.size();
                return std::make_unique<BaseModel>(nodeType, name, in, out);
            },
           PLUG::TypeStr(var.type)
        );
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
class connectClass{
public:
    QObject* in_obj;
    QString in_slot;
    QObject* out_obj;
    QString out_signal;
    bool operator==(const connectClass& other) const
    {
        return in_obj == other.in_obj && in_slot == other.in_slot && out_obj == other.out_obj && out_signal == other.out_signal;
    }
};
void NodeEditPage::_sceneLoaded()
{
    auto& model = scene->getGraphModel();
    auto allNodeIds = model.allNodeIds();
    QList<connectClass> connectList;
    for (auto& var : allNodeIds)
    {
        auto type = model.nodeData(var, NodeRole::Type).toString();
    }
    for (auto& var : allNodeIds)
    {
        auto cIds = model.allConnectionIds(var);

        for (auto& cid : cIds)
        {
            try
            {
                QObject* in_obj = ManageInterface::instance()->getObj(cid.inNodeId);
                QObject* out_obj = ManageInterface::instance()->getObj(cid.outNodeId);
               // qDebug() << "in:" << cid.inNodeId << in_obj << "out:" << cid.outNodeId << out_obj;

                if (!in_obj || !out_obj)
                {
                    throw std::runtime_error(QString("connection skipped because obj is null; inNodeId=%1 outNodeId=%2")
                                                 .arg(in_obj?in_obj->metaObject()->className():model.nodeData(cid.inNodeId,NodeRole::Type).toString())
                                                 .arg(out_obj?out_obj->metaObject()->className():QString::number(cid.outNodeId))
                                                 .toStdString());
                }

                auto* in_base = dynamic_cast<InterfaceBase*>(in_obj);
                auto* out_base = dynamic_cast<InterfaceBase*>(out_obj);
                if (!in_base || !out_base)
                {
                    throw std::runtime_error(
                        QString("%1: connection skipped because obj is not InterfaceBase; inNodeId=%2 outNodeId=%3")
                            .arg(in_base ? "out" : "in")
                            .arg(in_obj?in_obj->metaObject()->className():QString::number(cid.inNodeId))
                            .arg(out_obj?out_obj->metaObject()->className():QString::number(cid.outNodeId))
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
                            .arg(in_obj?in_obj->metaObject()->className():QString::number(cid.inNodeId))
                            .arg(cid.inPortIndex)
                            .arg(out_obj?out_obj->metaObject()->className():QString::number(cid.outNodeId))
                            .arg(cid.outPortIndex)
                            .toStdString());
                }

               auto ok = QObject::connect(out_obj, out_signal, in_obj, in_slot, Qt::UniqueConnection);
                if (!ok)
                {
                    if (!connectList.contains({out_obj, out_signal, in_obj, in_slot}))
                    {
                        // dumpMeta(in_obj);
                        // dumpMeta(out_obj);
                        throw std::runtime_error(
                        QString("%1(%2) %3 <===connect==> %4(%5) %6")
                                    .arg(out_obj->metaObject()->className())
                                    .arg(reinterpret_cast<quintptr>(out_obj), 0, 16)
                                    .arg(out_signal)
                                    .arg(in_obj->metaObject()->className())
                                    .arg(reinterpret_cast<quintptr>(in_obj), 0, 16)
                                    .arg(in_slot).toStdString());
                    }
                }
                else
                {
                    connectList.append({out_obj, out_signal, in_obj, in_slot});
                    qInfo()<<out_obj<<out_signal<<" <===connect==> "<<in_obj<<in_slot;
                }
            }
            catch (const std::exception& e)
            {
                qWarning()  << e.what();
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
void NodeEditPage::showConfigDialog(QObject* _obj, int index)
{
    auto obj = qobject_cast<IOInterface*>(_obj);
    auto io_obj = (IOInterface*)(_obj);
    QDialog d(this);
    auto config = obj->getConfig();

    QtTreePropertyBrowser editor(&d);
    QList<QtVariantProperty*> propertys;
    auto manager = new QtVariantPropertyManager(&d);
    for (auto& var : config)
    {

        QtVariantProperty* property;
        if (std::get<0>(var) == QVariant::StringList)
        {
            property = manager->addProperty(QtVariantPropertyManager::enumTypeId(), std::get<1>(var));
            // qDebug()<<std::get<2>(var);
            property->setAttribute(QLatin1String("enumNames"), std::get<2>(var));
            property->setValue(0);
        }
        else
        {
            property = manager->addProperty(std::get<0>(var), std::get<1>(var));
            property->setValue(std::get<2>(var));
        }
        editor.addProperty(property);
        propertys.append(property);
    }
    QtVariantEditorFactory* variantFactory = new QtVariantEditorFactory(&d);

    editor.setFactoryForManager(manager, variantFactory);
    editor.setPropertiesWithoutValueMarked(true);
    editor.setRootIsDecorated(false);
    QVBoxLayout layout(&d);
    layout.addWidget(&editor);
    auto fun = [&]()
    {
        for (int i = 0; i < config.size(); i++)
        {
            if (std::get<0>(config[i]) == QVariant::StringList)
            {
                auto index = propertys.at(i)->value().toInt();
                std::get<2>(config[i]) = propertys.at(i)->attributeValue("enumNames").toStringList().at(index);
            }
            else
                std::get<2>(config[i]) = propertys.at(i)->value();
        }
        obj->setConfig(config);
        _saveConfig(index,config);
    };
    QHBoxLayout  vb;
    if (auto io= static_cast<IOInterface*>(obj))
    {

        auto openBtn=new QPushButton("打开",&d);
        auto closeBtn=new QPushButton("关闭",&d);
        vb.addWidget(openBtn);
        vb.addWidget(closeBtn);
        layout.addLayout(&vb);

        connect(openBtn,&QPushButton::clicked,this,[&]()
        {
            fun();
            io->open();
        });
        connect(closeBtn,&QPushButton::clicked,this,[&]()
        {
            fun();
            io->close();
        });
    }
    d.adjustSize();
    connect(io_obj,&IOInterface::statusChanged,this,[&]()
    {
        if ( io_obj->status() == PLUG::OPEN_STATUS )
        {
            d.close();
        }
    });
    d.exec();
    fun();
}
/**
 *a
 * @param index
 * @param config
 */
void NodeEditPage::_saveConfig(int index, const QList<std::tuple<QVariant::Type, QString, QVariant>>& config)
{
    QFile file(configPath);

    // 1. 读取已有 JSON（不存在则创建）
    QJsonObject root;
    if (file.exists())
    {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
        file.close();

        if (error.error != QJsonParseError::NoError)
            return;

        root = doc.object();
    }

    // 2. 取得 NodeEditPage 数组
    QJsonArray nodeEditPage = root.value("NodeEditPage").toArray();

    // 3. 构造新的 config 对象
    QJsonObject obj;
    obj["key"] = index;

    QJsonArray array;
    for (const auto& var : config)
    {
        QJsonObject temp;
        temp["type"] = static_cast<int>(std::get<0>(var));
        temp["name"] = std::get<1>(var);
        temp["value"] = QJsonValue::fromVariant(std::get<2>(var));
        array.append(temp);
    }
    obj["config"] = array;

    // 4. key 唯一处理（存在则替换）
    bool replaced = false;
    for (int i = 0; i < nodeEditPage.size(); ++i)
    {
        QJsonObject item = nodeEditPage[i].toObject();
        if (item.value("key").toInt() == index)
        {
            nodeEditPage[i] = obj;
            replaced = true;
            break;
        }
    }

    if (!replaced)
    {
        nodeEditPage.append(obj);
    }

    root["NodeEditPage"] = nodeEditPage;

    // 5. 写回文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        return;

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();
}
QList<int> NodeEditPage::_allIndexes() const
{
    QList<int> indexes;

    QFile file(configPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return indexes;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    file.close();

    if (error.error != QJsonParseError::NoError || !doc.isObject())
    {
        return indexes;
    }

    QJsonArray nodeEditPage = doc.object().value("NodeEditPage").toArray();

    for (const QJsonValue& v : nodeEditPage)
    {
        QJsonObject obj = v.toObject();
        if (obj.contains("key"))
        {
            indexes.append(obj.value("key").toInt());
        }
    }

    return indexes;
}
QList<std::tuple<QVariant::Type, QString, QVariant>> NodeEditPage::_loadConfig(int index)
{
    QList<std::tuple<QVariant::Type, QString, QVariant>> result;

    QFile file(configPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return result;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    file.close();

    if (error.error != QJsonParseError::NoError || !doc.isObject()) {
        return result;
    }

    QJsonArray nodeEditPage = doc.object().value("NodeEditPage").toArray();

    // 查找 key
    for (const QJsonValue& v : nodeEditPage) {
        QJsonObject obj = v.toObject();
        if (obj.value("key").toInt() != index)
            continue;

        QJsonArray cfgArray = obj.value("config").toArray();
        for (const QJsonValue& c : cfgArray) {
            QJsonObject temp = c.toObject();

            QVariant::Type type =
                static_cast<QVariant::Type>(temp.value("type").toInt());
            QString name = temp.value("name").toString();
            QVariant value = temp.value("value").toVariant();

            result.append(std::make_tuple(type, name, value));
        }
        break; // key 唯一，找到即可退出
    }

    return result;
}
NodeEditPage::NodeEditPage(QWidget* parent)
    :GraphicsView(parent)
    ,registry( _registerDataModels())
    ,dataFlowGraphModel(new DataFlowGraphModel(registry))
    ,scene(new DataFlowGraphicsScene(*dataFlowGraphModel))
    ,configPath(QStandardPaths::writableLocation(
                    QStandardPaths::AppConfigLocation
                )+"/config.json")
{
    //foreach(auto &var:ManageInterface::instance())
    //{
//
    //}
    //QList<QtNodes::NodeDataTypeEnum::InputType> in = {QtNodes::NodeDataTypeEnum::IN_IO_TX};
    //QList<QtNodes::NodeDataTypeEnum::OutputType> out = {QtNodes::NodeDataTypeEnum::OUT_IO_TX};
    //registry->registerModel<BaseModel>(
    //    [in, out]() {
    //        return std::make_unique<BaseModel>(BaseModel::IO_TYPE, "IO", in, out);
    //    },
    //    "IO");
    connect(dataFlowGraphModel,&DataFlowGraphModel::configClicked,this,[this](int index)
    {
            //TODO
        if (auto obj =qobject_cast<IOInterface*>(ManageInterface::instance()->getObj(index)))
        {
            qInfo()<<"configClicked "<<index<<obj;
            auto config =obj->getConfig();

            showConfigDialog(ManageInterface::instance()->getObj(index),index);
        }
        else  if (auto obj =qobject_cast<IOAPPInterface*>(ManageInterface::instance()->getObj(index)))
        {
            qInfo()<<"IOAPPInterface configClicked "<<index<<obj;
             showConfigDialog(ManageInterface::instance()->getObj(index),index);
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
        try
        {
            this->scene->load(this->scene->getDefaultConfigPath());
            auto indexes = _allIndexes();
            for (int index : indexes) {
                auto cfg = _loadConfig(index);
                //auto obj = Manage::getInterfaceBase(index);
                //if (obj)
                //{
                //    obj->setConfig(cfg);
                //}
            }
        }
        catch (const std::logic_error& e) {
            QMessageBox::warning(this,"警告","节点配置文件加载失败："+QString(e.what()));
           qWarning() << e.what();
        }
}
