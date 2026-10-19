//
// Created by 25137 on 25-12-21.
//

#include "nodemodel.h"
#include "plug\interfacecommon.h"
#include <utility>
#include <QLabel>
#include <QPluginLoader>
using namespace QtNodes;

 QMap<PLUG::Type,BaseModel::NodeTye> BaseModel::plugTypeMap{
    {PLUG::Type::Default,DEFAULT_TYPE},
    {PLUG::Type::VIEW,IO_TYPE},
    {PLUG::Type::IO,IOAPP_TYPE},
    {PLUG::Type::IOAPP,VIEW_TYPE},
    {PLUG::Type::SIGNAL,SIGNAL_TYPE}
};
 QMap<PLUG::InputType,QtNodes::NodeDataTypeEnum::InputType> BaseModel::inputTypeMap{
        {PLUG::InputType::IN_VIRTUAL_TX ,QtNodes::NodeDataTypeEnum::IN_VIRTUAL_TX},
        {PLUG::InputType::IN_IO_TX      ,QtNodes::NodeDataTypeEnum::IN_IO_TX},
        {PLUG::InputType::IN_IO_RX      ,QtNodes::NodeDataTypeEnum::IN_IO_RX},
        {PLUG::InputType::IN_APP_TX     ,QtNodes::NodeDataTypeEnum::IN_APP_TX},
        {PLUG::InputType::IN_APP_RX     ,QtNodes::NodeDataTypeEnum::IN_APP_RX},
        {PLUG::InputType::IN_APP_SIGNAL ,QtNodes::NodeDataTypeEnum::IN_APP_SIGNAL}
};
 QMap<PLUG::OutputType,QtNodes::NodeDataTypeEnum::OutputType> BaseModel::outputTypeMap{
    {PLUG::OutputType::OUT_IO_TX        ,QtNodes::NodeDataTypeEnum::OUT_IO_TX},
    {PLUG::OutputType::OUT_IO_RX        ,QtNodes::NodeDataTypeEnum::OUT_IO_RX},
    {PLUG::OutputType::OUT_APP_TX       ,QtNodes::NodeDataTypeEnum::OUT_APP_TX},
    {PLUG::OutputType::OUT_APP_RX       ,QtNodes::NodeDataTypeEnum::OUT_APP_RX},
    {PLUG::OutputType::OUT_APP_SIGNAL   ,QtNodes::NodeDataTypeEnum::OUT_APP_SIGNAL}
};
QMap<PLUG::InputType,PLUG::OutputType> BaseModel::inputTOoutput{
    {PLUG::InputType::IN_IO_TX      ,PLUG::OutputType::OUT_IO_TX        },
    {PLUG::InputType::IN_IO_RX      ,PLUG::OutputType::OUT_IO_RX        },
    {PLUG::InputType::IN_APP_TX     ,PLUG::OutputType::OUT_APP_TX       },
    {PLUG::InputType::IN_APP_RX     ,PLUG::OutputType::OUT_APP_RX       },
    {PLUG::InputType::IN_APP_SIGNAL ,PLUG::OutputType::OUT_APP_SIGNAL   }
};

BaseModel::BaseModel(QString plugPath
      ,NodeTye type,QString _name,QList<PLUG::InputType> _in,QList<PLUG::OutputType> _out)
    :
    m_plugPath(std::move(plugPath)),
    m_type(type), m_name(std::move(_name)), in(_in),out(_out)
{
    m_caption=m_name;
   m_plug.reset(new PlugLoader(m_plugPath,this));

    m_widget.reset( new QPushButton("配置"));
    if (QFile qss(QStringLiteral(":/configbtn.qss"));
    qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_widget->setStyleSheet(qss.readAll());
    }
    QObject::connect(qobject_cast<QPushButton*>(m_widget.get()),&QPushButton::clicked,this,[this]()
    {emit configClicked(this);});
}
unsigned int BaseModel::nPorts(PortType const portType) const
{
    unsigned int result = 1;

    switch (portType)
    {
    case PortType::In:
        result = in.size();
        break;
    case PortType::Out:
        result = out.size();
        break;
    case PortType::None:
    default:break;
    }

    return result;
}

NodeDataType BaseModel::dataType(PortType const portType, PortIndex const portIndex) const
{
    switch (portType) {
    case PortType::In:
    {
        return INNodeData(InputPLUG_TO_NODE_InputTYPE(in.at(portIndex))).type();
    }
    case PortType::Out:
        return OUTNodeData(OutputPLUG_TO_NODE_OutputTYPE(out.at(portIndex))).type();

    case PortType::None:
        break;
    }
    // FIXME: control may reach end of non-void function [-Wreturn-type]
    return NodeDataType();
}

std::shared_ptr<NodeData> BaseModel::outData(PortIndex const port)
{
    return {};
}
/*
IOModel::IOModel(QString name):BaseModel(IO_TYPE,std::move(name)
        ,{TypeEnum::IN_VIRTUAL_TX,TypeEnum::IN_IO_TX}
        ,{TypeEnum::OUT_IO_RX})
{
    m_widget =( new QPushButton("配置"));
    if (QFile qss(QStringLiteral(":/configbtn.qss"));
    qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_widget->setStyleSheet(qss.readAll());
    }
    QObject::connect(qobject_cast<QPushButton*>(m_widget),&QPushButton::clicked,this,[this]()
    {
        emit configClicked(QPoint());
       //Manage::showConfig(this);
       // QMessageBox::information(nullptr,"IOModel","IOModel");
    });
};

IOAPPModel::IOAPPModel(QString name):BaseModel(IOAPP_TYPE,std::move(name)
   ,{TypeEnum::IN_IO_RX,TypeEnum::IN_APP_TX}
   ,{TypeEnum::OUT_IO_TX,TypeEnum::OUT_APP_RX,TypeEnum::OUT_APP_SIGNAL})
{
    m_widget =( new QPushButton("配置"));
    if (QFile qss(QStringLiteral(":/configbtn.qss"));
    qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_widget->setStyleSheet(qss.readAll());
    }

    QObject::connect(qobject_cast<QPushButton*>(m_widget),&QPushButton::clicked,this,[this]()
    {
        emit configClicked(QPoint());
       //Manage::showConfig(this);
       // QMessageBox::information(nullptr,"IOModel","IOModel");
    });
 */