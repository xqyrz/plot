//
// Created by 25137 on 26-1-10.
//

#ifndef INTERFACEBASE_H
#define INTERFACEBASE_H
#include <QVariant>
#include <QObject>
#include <QMap>
#include <QDebug>
//#include "../../../lib/mdb/mdb.h"

namespace Plug
{
    enum InputType {          // 更好的命名
        IN_VIRTUAL_TX,
        IN_IO_TX,
        IN_IO_RX,
        IN_APP_TX,
        IN_APP_RX,
        IN_APP_SIGNAL
    };

    enum OutputType {        // 更好的命名
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
    virtual const char* getSignal(int index) const=0;
    virtual const char* getSlot(int index) const=0;
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
protected:
    QMap<QString,  std::function<void(const void*)>> m_funs;
     int m_type = DefaultEnum;
     QString m_name = "UNKNOW";
};
#endif //INTERFACEBASE_H
