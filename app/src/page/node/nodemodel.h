//
// Created by 25137 on 25-12-21.
//

#ifndef NODEMODEL_H
#define NODEMODEL_H

#include <QtNodes/NodeDelegateModel>

#include <QPushButton>
#include <memory>
#include <utility>
#include <QPluginLoader>
#include "nodedata.h"
#include "obj/signalobj.h"
class InterfaceBase;
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
 //   Q_ENUM(NodeTye);

  //BaseModel():NodeDelegateModel(),m_type(DEFAULT_TYPE){};
  BaseModel(
      QString plugPath
      ,const NodeTye type
      ,const QString _name
      ,const QList<PLUG::InputType> _in
      ,const QList<PLUG::OutputType> _out);

    virtual ~BaseModel() override
    {
    }
    BaseModel(const BaseModel &other):BaseModel(other.m_plugPath,other.m_type,other.m_name,other.in,other.out){};

    BaseModel( BaseModel &&other)noexcept:
    m_plugPath(std::move(other.m_plugPath)),
    m_type(other.m_type),
    m_name(other.m_name),
    m_caption(other.m_caption),
    in(other.in),
    out(other.out),
    m_plug (other.m_plug.take())
    {
    };
    BaseModel& operator=(BaseModel&& other)noexcept
    {
        if (this != &other)
        {
            m_type = other.m_type;
            m_name = std::move(other.m_name);
            m_caption = std::move(other.m_caption);
            in = std::move(other.in);
            out = std::move(other.out);
            m_plug.reset(other.m_plug.take());
        }
        return *this;
    }
    BaseModel& operator=(const BaseModel& other)
    {
        if (this != &other)
        {
            m_type = other.m_type;
            m_name = other.m_name;
            m_caption = other.m_caption;
            in = other.in;
            out = other.out;
            m_plug.reset(new QPluginLoader(m_plugPath,this));
        }
        return *this;
    }

    static NodeTye PLUG_TO_NODE_TYPE(const PLUG::Type& plug)
    {
        return plugTypeMap.value(plug);
    }
    static QtNodes::NodeDataTypeEnum::InputType InputPLUG_TO_NODE_InputTYPE(const PLUG::InputType& inputType)
    {
        return inputTypeMap.value(inputType);
    }
    static QtNodes::NodeDataTypeEnum::OutputType OutputPLUG_TO_NODE_OutputTYPE(const PLUG::OutputType& inputType)
    {
        return outputTypeMap.value(inputType);
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
    QObject *obj()override{return m_plug->instance();};
private:
    //void setObj(InterfaceBase* _obj){m_obj =_obj;};
public:
    static QMap<PLUG::Type,NodeTye> plugTypeMap;
    static QMap<PLUG::InputType,QtNodes::NodeDataTypeEnum::InputType> inputTypeMap;
    static QMap<PLUG::OutputType,QtNodes::NodeDataTypeEnum::OutputType> outputTypeMap;
    static QMap<PLUG::InputType,PLUG::OutputType> inputTOoutput;

protected:
    QString m_plugPath;
    NodeTye m_type=DEFAULT_TYPE;
    QString m_name;
    QString m_caption;
    QList<PLUG::InputType> in;
    QList<PLUG::OutputType> out;
    QWidget* m_widget=nullptr;
    QScopedPointer<QPluginLoader> m_plug;

};


#endif //NODEMODEL_H
