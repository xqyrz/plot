//
// Created by 25137 on 25-12-21.
//

#ifndef NODEMODEL_H
#define NODEMODEL_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModel>

#include <memory>
#include <utility>
#include "nodedata.h"
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;





class IOModel : public NodeDelegateModel
{
Q_OBJECT
public:
    typedef enum {
        DEFAULT_TYPE,
        IO_TYPE,
        IOAPP_TYPE,
        VIEW_TYPE
      }NodeTye;

  IOModel():NodeDelegateModel(),m_type(DEFAULT_TYPE){};
  IOModel(NodeTye type,QString _name);

    virtual ~IOModel() override {}

public:
    QString caption() const override { return m_caption; }

    QString name() const override { return m_name; }

public:
    unsigned int nPorts(PortType const portType) const override;

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex const port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex const) override{};

    QWidget *embeddedWidget() override { return nullptr; }
private:
    QString m_caption;
    QString m_name;
    QList<QtNodes::NodeDataTypeEnum::InputType> in;
    QList<QtNodes::NodeDataTypeEnum::OutputType> out;
    NodeTye m_type;
};




#endif //NODEMODEL_H
