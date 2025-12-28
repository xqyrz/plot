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





class BaseModel : public NodeDelegateModel
{
Q_OBJECT
public:
    typedef enum {
        DEFAULT_TYPE,
        IO_TYPE,
        IOAPP_TYPE,
        VIEW_TYPE
      }NodeTye;

  BaseModel():NodeDelegateModel(),m_type(DEFAULT_TYPE){};
  BaseModel(NodeTye type,QString _name,QList<QtNodes::NodeDataTypeEnum::InputType> _in,QList<QtNodes::NodeDataTypeEnum::OutputType> _out);

    virtual ~BaseModel() override {}

public:
    QString caption() const override { return m_caption; }

    QString name() const override { return m_name; }

public:
    unsigned int nPorts(PortType const portType) const override;

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex const port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex const) override{};

    QWidget *embeddedWidget() override;
protected:
    NodeTye m_type=DEFAULT_TYPE;
    QString m_name;
    QString m_caption;
     QList<QtNodes::NodeDataTypeEnum::InputType> in;
     QList<QtNodes::NodeDataTypeEnum::OutputType> out;
private:

    QWidget* m_widget=nullptr;
};


class IOModel:public BaseModel
{
    using TypeEnum=QtNodes::NodeDataTypeEnum;
public:
    IOModel(QString name):BaseModel(IO_TYPE,std::move(name)
        ,{TypeEnum::IN_VIRTUAL_TX,TypeEnum::IN_IO_TX}
        ,{TypeEnum::OUT_IO_RX}){};
private:
};

class IOAPPModel:public BaseModel
{
    using TypeEnum=QtNodes::NodeDataTypeEnum;
public:
    IOAPPModel(QString name):BaseModel(IOAPP_TYPE,std::move(name)
        ,{TypeEnum::IN_IO_RX,TypeEnum::IN_APP_TX}
        ,{TypeEnum::OUT_IO_TX,TypeEnum::OUT_APP_RX,TypeEnum::OUT_APP_SIGNAL}){};
private:
};

class ViewModel:public BaseModel
{
    using TypeEnum=QtNodes::NodeDataTypeEnum;
public:
    ViewModel(QString name):BaseModel(VIEW_TYPE,std::move(name)
        ,{TypeEnum::IN_APP_RX,TypeEnum::IN_APP_SIGNAL}
        ,{TypeEnum::OUT_APP_TX}){};
private:
};

#endif //NODEMODEL_H
