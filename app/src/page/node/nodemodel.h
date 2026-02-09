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
#include "interface/manage.h"
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

;
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

class ViewModel:public BaseModel
{
    using TypeEnum=QtNodes::NodeDataTypeEnum;
public:
    ViewModel(QString name):BaseModel(VIEW_TYPE,std::move(name)
        ,{TypeEnum::IN_APP_RX,TypeEnum::IN_APP_SIGNAL}
        ,{TypeEnum::OUT_APP_TX}){};
private:
};


class AppSignalModel:public BaseModel
{
    using TypeEnum=QtNodes::NodeDataTypeEnum;
public:
    AppSignalModel(QString name):BaseModel(SIGNAL_TYPE,std::move(name)
        ,{TypeEnum::IN_APP_SIGNAL
            ,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL
            ,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL
            ,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL,TypeEnum::IN_APP_SIGNAL
        }
        ,{TypeEnum::OUT_APP_SIGNAL}){};
private:
};

class AppRxModel:public BaseModel
{
    using TypeEnum=QtNodes::NodeDataTypeEnum;
public:
    AppRxModel(QString name):BaseModel(SIGNAL_TYPE,std::move(name)
        ,{TypeEnum::IN_IO_RX
            ,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX
            ,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX
            ,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX,TypeEnum::IN_IO_RX
        }
        ,{TypeEnum::OUT_IO_RX}){};
private:
};
#endif //NODEMODEL_H
