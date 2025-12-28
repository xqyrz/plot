//
// Created by 25137 on 25-12-21.
//

#include "nodemodel.h"

#include <utility>
#include <QLabel>
using namespace QtNodes;
BaseModel::BaseModel(NodeTye type,QString _name,QList<QtNodes::NodeDataTypeEnum::InputType> _in,QList<QtNodes::NodeDataTypeEnum::OutputType> _out)
    :m_type(type), m_name(std::move(_name)), in(std::move(_in)),out(std::move(_out))
{
    m_caption=m_name;

}
unsigned int BaseModel::nPorts(PortType const portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:result = in.size();break;
    case PortType::Out:result = out.size();break;
    case PortType::None:
    default:break;
    }

    return result;
}

NodeDataType BaseModel::dataType(PortType const portType, PortIndex const portIndex) const
{
    switch (portType) {
    case PortType::In:
        return INNodeData(in.at(portIndex)).type();

    case PortType::Out:
        return OUTNodeData(out.at(portIndex)).type();

    case PortType::None:
        break;
    }
    // FIXME: control may reach end of non-void function [-Wreturn-type]
    return NodeDataType();
}

std::shared_ptr<NodeData> BaseModel::outData(PortIndex const port)
{
    // qWarning()<<".........."<<out.at(port);
    return std::make_shared<OUTNodeData>(OUTNodeData(out.at(port)));
    // if (port < 1)return std::make_shared<MyNodeData>();
    // return std::make_shared<SimpleNodeData>();
}
QWidget* BaseModel::embeddedWidget()
{
    return m_widget;
}
