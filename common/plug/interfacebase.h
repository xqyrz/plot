//
// Created by 25137 on 26-1-10.
//

#ifndef INTERFACEBASE_H
#define INTERFACEBASE_H
#include <QVariant>
#include <QObject>
#include <QMap>
#include <QDebug>
#include "interfacecommon.h"
//#include "../../../lib/mdb/mdb.h"

namespace Plug
{
    enum class InputType {          // 更好的命名
        IN_VIRTUAL_TX,
        IN_IO_TX,
        IN_IO_RX,
        IN_APP_TX,
        IN_APP_RX,
        IN_APP_SIGNAL
    };

    enum class OutputType {        // 更好的命名
        OUT_IO_TX,
        OUT_IO_RX,
        OUT_APP_TX,
        OUT_APP_RX,
        OUT_APP_SIGNAL,
    };

    enum class  Type
    {
        Default,
        VIEW,
        IO,
        IOAPP,
        SIGNAL,
    };
}
class InterfaceBase:public QObject {
    Q_OBJECT
public:
    typedef enum
    {
        IOOBJS
    }KEYS;
    inline static const char* const keyStr(const KEYS key)
    {
        switch (key)
        {
        case IOOBJS:return "IOOBJS";
            default:Q_ASSERT(1);
        }
        return nullptr;
    }
    InterfaceBase(QObject* parent=nullptr):QObject(parent)
    {
       // MDB::instance()->add(keyStr(IOOBJS),reinterpret_cast<uintptr_t>(this));
    };
    virtual ~InterfaceBase()
    {
       // qDebug() << "~InterfaceBase()";
    }
    const char* getSignal(Plug::InputType index) const;
    const char* getSlot(Plug::OutputType index) const;
    const char* getSignal(int index) const{return getSignal(m_inputPorts.at(index));};
    const char* getSlot(int index) const{return getSlot(m_outputPorts.at(index));};
    QList<Plug::InputType> inputPorts()const{return m_inputPorts;}
    QList<Plug::OutputType> outputPorts()const{return m_outputPorts;}
    virtual QList<std::tuple<QVariant::Type,QString,QVariant>> getConfig(){return {};};
    virtual void setConfig(const QList<std::tuple<QVariant::Type,QString,QVariant>> &){};
    void fun(const QString& key,const void * value)
    {
        if (m_funs.contains(key))
        {
            m_funs[key](value);
        }
    }
    QString getName() const { return m_name; }
    int getType() const { return m_type; }

    enum
    {
        DefaultEnum,
        IOInterfaceEnum,
    };
signals:
void signals_OUT_IO_TX(const INC::Frame&);
void signals_OUT_IO_RX(const INC::Frame&);
void signals_OUT_APP_TX(const INC::Frame&);
void signals_OUT_APP_RX(const INC::Frame&);
void signals_OUT_APP_SIGNAL(const QList<INC::_SIGNALS>&);
public slots:
void slots_IN_VIRTUAL_TX(const INC::Frame&);
void slots_IN_IO_TX(const INC::Frame&);
void slots_IN_IO_RX(const INC::Frame&);
void slots_IN_APP_TX(const INC::Frame&);
void slots_IN_APP_RX(const INC::Frame&);
void slots_IN_APP_SIGNAL(const QList<INC::_SIGNALS>&);
protected:
    QMap<QString,  std::function<void(const void*)>> m_funs;
     int m_type = DefaultEnum;
     QString m_name = "UNKNOW";
    QList<Plug::InputType> m_inputPorts;
    QList<Plug::OutputType> m_outputPorts;

};
#endif //INTERFACEBASE_H
