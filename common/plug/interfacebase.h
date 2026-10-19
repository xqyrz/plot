//
// Created by 25137 on 26-1-10.
//

#ifndef INTERFACEBASE_H
#define INTERFACEBASE_H
#include <QDebug>
#include "interfacecommon.h"
//#include "../../../lib/mdb/mdb.h"


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
    };
    virtual ~InterfaceBase()
    {
    }
    const char* getSignal(PLUG::InputType index) const;
    const char* getSlot(PLUG::OutputType index) const;
    const char* getSignal(int index) const{return getSignal(m_inputPorts.at(index));};
    const char* getSlot(int index) const{return getSlot(m_outputPorts.at(index));};
    QList<PLUG::InputType> inputPorts()const{return m_inputPorts;}
    QList<PLUG::OutputType> outputPorts()const{return m_outputPorts;}
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
    void signals_IN_VIRTUAL_TX(const PLUG::Frame&);
    void signals_IN_IO_TX(const PLUG::Frame&);
    void signals_IN_IO_RX(const PLUG::Frame&);
    void signals_IN_APP_TX(const PLUG::Frame&);
    void signals_IN_APP_RX(const PLUG::Frame&);
    void signals_IN_APP_SIGNAL(const QList<PLUG::_SIGNALS>&);

public slots:
    void slots_OUT_IO_TX(const PLUG::Frame&);
    void slots_OUT_IO_RX(const PLUG::Frame&);
    void slots_OUT_APP_TX(const PLUG::Frame&);
    void slots_OUT_APP_RX(const PLUG::Frame&);
    void slots_OUT_APP_SIGNAL(const QList<PLUG::_SIGNALS>&);
protected:
    QMap<QString,  std::function<void(const void*)>> m_funs;
     int m_type = DefaultEnum;
     QString m_name = "UNKNOW";
    QList<PLUG::InputType> m_inputPorts;
    QList<PLUG::OutputType> m_outputPorts;

};
#endif //INTERFACEBASE_H
