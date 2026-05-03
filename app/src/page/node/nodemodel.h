//
// Created by 25137 on 25-12-21.
//

#ifndef NODEMODEL_H
#define NODEMODEL_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtNodes/NodeDelegateModel>

#include <QPushButton>
#include <memory>
#include <utility>
#include "nodedata.h"
#include "obj/signalobj.h"
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
        VIEW_TYPE,
        SIGNAL_TYPE
      }NodeTye;
    Q_ENUM(NodeTye);

  BaseModel():NodeDelegateModel(),m_type(DEFAULT_TYPE){};
  BaseModel(NodeTye type,QString _name,QList<QtNodes::NodeDataTypeEnum::InputType> _in,QList<QtNodes::NodeDataTypeEnum::OutputType> _out);

    virtual ~BaseModel() override
    {
        if (m_widget)m_widget->deleteLater();
    }
    BaseModel(const BaseModel &other):m_type(other.m_type),m_name(other.m_name),m_caption(other.m_caption),in(other.in),out(other.out){

    }
    BaseModel( BaseModel &&other):m_type(other.m_type),m_name(other.m_name),m_caption(other.m_caption),in(other.in),out(other.out){

    }
    BaseModel& operator=(BaseModel&& other)
    {
        if (this != &other)
        {
            m_type = other.m_type;
            m_name = std::move(other.m_name);
            m_caption = std::move(other.m_caption);
            in = std::move(other.in);
            out = std::move(other.out);
        }
        return *this;
    }
    BaseModel& operator=(const BaseModel& other)
    {
        if (this != &other)
        {
            m_type = other.m_type;
            m_name = std::move(other.m_name);
            m_caption = std::move(other.m_caption);
            in = std::move(other.in);
            out = std::move(other.out);
        }
        return *this;
    }
public:
    QString caption() const override { return m_caption; }

    QString name() const override { return m_name; }
    NodeTye type()const {return m_type;};
public:
    unsigned int nPorts(PortType const portType) const override;

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex const port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex const) override{};

    bool resizable() const override { return true; }
    QWidget *embeddedWidget() override{return nullptr;}
private:
    void setObj(QObject* _obj){obj =_obj;};
protected:
    NodeTye m_type=DEFAULT_TYPE;
    QString m_name;
    QString m_caption;
    QList<QtNodes::NodeDataTypeEnum::InputType> in;
    QList<QtNodes::NodeDataTypeEnum::OutputType> out;
protected:

    QWidget* m_widget=nullptr;
    QObject* obj;
};


class IOModel:public BaseModel
{
    using TypeEnum=QtNodes::NodeDataTypeEnum;
public:
    IOModel(QString name);
    QWidget *embeddedWidget() override
    {
        return m_widget;
    }
private:
};

class IOAPPModel:public BaseModel
{
    using TypeEnum=QtNodes::NodeDataTypeEnum;
public:
     IOAPPModel(QString name);
    QWidget *embeddedWidget() override
    {
        return m_widget;
    }
private:
};

class PortModel:public BaseModel{
    using TypeEnum=QtNodes::NodeDataTypeEnum;
public:
    PortModel(QString name):BaseModel()
    {
        this->m_type = SIGNAL_TYPE;
        this->m_name = name;
        this->m_caption = name;
        auto key =SIGNALDATA::SIGNALS_ENUM_DATA.key(name);
        switch (key)
        {
            case SIGNALDATA::IO_RX:
            this->in = {TypeEnum::IN_IO_RX
            ,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX
            ,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX
            ,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX
            };
            this->out = {TypeEnum::OUT_IO_RX};
            break;
            case SIGNALDATA::APP_SIGNAL:
            this->in={TypeEnum::IN_APP_SIGNAL
            ,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL
            ,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL
            ,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL
            };
            this->out = {TypeEnum::OUT_APP_SIGNAL};
            break;
            case SIGNALDATA::APP_RX:
            this->in = {TypeEnum::IN_APP_RX
            ,TypeEnum::IN_APP_RX,TypeEnum::IN_APP_RX,TypeEnum::IN_APP_RX
            ,TypeEnum::IN_APP_RX,TypeEnum::IN_APP_RX,TypeEnum::IN_APP_RX
            ,TypeEnum::IN_APP_RX,TypeEnum::IN_APP_RX,TypeEnum::IN_APP_RX
            };
            this->out = {TypeEnum::OUT_APP_RX};
            break;
        }
    };
private:
};


#endif //NODEMODEL_H
