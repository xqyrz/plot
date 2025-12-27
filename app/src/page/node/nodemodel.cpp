//
// Created by 25137 on 25-12-21.
//

#include "nodemodel.h"

#include <utility>

using namespace QtNodes;
IOModel::IOModel(NodeTye type, QString _name)
{
    m_type=type;
    m_name=std::move(_name);
    m_caption=m_name;
    switch (type)
    {
    case DEFAULT_TYPE:
        break;
    case IO_TYPE:
    {
        in<<NodeDataTypeEnum::IN_VIRTUAL_TX<<NodeDataTypeEnum::IN_IO_TX;
        out<<NodeDataTypeEnum::OUT_IO_RX;
    }
        break;
    case IOAPP_TYPE:
    {
        in<<NodeDataTypeEnum::IN_IO_RX<<NodeDataTypeEnum::IN_APP_TX;
        out
        <<NodeDataTypeEnum::OUT_IO_TX
        <<NodeDataTypeEnum::OUT_APP_RX
        <<NodeDataTypeEnum::OUT_APP_SIGNAL;
    }
        break;
    case VIEW_TYPE:
    {
        in<<NodeDataTypeEnum::IN_APP_RX<<NodeDataTypeEnum::IN_APP_SIGNAL;
        out<<NodeDataTypeEnum::OUT_APP_TX;
    }
        break;
    default:
        break;
    }

}
unsigned int IOModel::nPorts(PortType const portType) const
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

NodeDataType IOModel::dataType(PortType const portType, PortIndex const portIndex) const
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

std::shared_ptr<NodeData> IOModel::outData(PortIndex const port)
{
 // qWarning()<<".........."<<out.at(port);
  return std::make_shared<OUTNodeData>(OUTNodeData(out.at(port)));
    // if (port < 1)return std::make_shared<MyNodeData>();
    // return std::make_shared<SimpleNodeData>();
}
