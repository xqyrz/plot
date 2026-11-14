//
// Created by 25137 on 26-1-10.
//

#ifndef INTERFACEBASE_H
#define INTERFACEBASE_H
#include <QDebug>
#include "interfacecommon.h"
//#include "../../../lib/mdb/mdb.h"

// InterfaceBase 被多个插件 DLL 各自编译，因此导出必须“按目标”显式开启：
//   INTERFACEBASE_EXPORTS   -> 由导出它的 DLL(plotpage) 定义，声明为 dllexport
//   INTERFACEBASE_DLL_IMPORT-> 由链接该 DLL 的消费方(如 opencvTest) 定义，声明为 dllimport
//   两者都未定义时保持原状（内部符号），避免其他插件库编译报错
#if defined(INTERFACEBASE_EXPORTS)
#  define INTERFACEBASE_EXPORT Q_DECL_EXPORT
#elif defined(INTERFACEBASE_DLL_IMPORT)
#  define INTERFACEBASE_EXPORT Q_DECL_IMPORT
#else
#  define INTERFACEBASE_EXPORT
#endif

class INTERFACEBASE_EXPORT InterfaceBase : public QObject {
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
    const char* getSignal(PLUG::OutputType index) const;
    const char* getSlot(PLUG::InputType index) const;
    const char* getSignal(int index) const
    {
        if ( m_outputPorts.size()> index)
        return getSignal(m_outputPorts.at(index));
        else return nullptr;;
    };
    const char* getSlot(int index) const
    {
        if ( m_inputPorts.size()> index)
        return getSlot(m_inputPorts.at(index));
        else return nullptr;;
    };
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

    void signals_OUT_IO_TX(const PLUG::Frame&);
    void signals_OUT_IO_RX(const PLUG::Frame&);
    void signals_OUT_APP_TX(const PLUG::Frame&);
    void signals_OUT_APP_RX(const PLUG::Frame&);
    void signals_OUT_APP_SIGNAL(const QList<PLUG::_SIGNALS>&);
public slots:
    virtual void slots_IN_VIRTUAL_TX(const PLUG::Frame&);
    virtual void slots_IN_IO_TX(const PLUG::Frame&);
    virtual void slots_IN_IO_RX(const PLUG::Frame&);
    virtual void slots_IN_APP_TX(const PLUG::Frame&);
    virtual void slots_IN_APP_RX(const PLUG::Frame&);
    virtual void slots_IN_APP_SIGNAL(const QList<PLUG::_SIGNALS>&);
protected:
    QMap<QString,  std::function<void(const void*)>> m_funs;
     int m_type = DefaultEnum;
     QString m_name = "UNKNOW";
    QList<PLUG::InputType> m_inputPorts;
    QList<PLUG::OutputType> m_outputPorts;

};
#endif //INTERFACEBASE_H
