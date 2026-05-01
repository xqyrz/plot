//
// Created by 25137 on 26-1-10.
//

#ifndef INTERFACEBASE_H
#define INTERFACEBASE_H
#include <QVariant>
#include <QObject>

class InterfaceBase {
public:
    virtual ~InterfaceBase() = default;
    virtual const char* getSignal(int index) const=0;
    virtual const char* getSlot(int index) const=0;
    virtual QList<std::tuple<QVariant::Type,QString,QVariant>> getConfig(){return {};};
    virtual void setConfig(const QList<std::tuple<QVariant::Type,QString,QVariant>> &){};
};
#endif //INTERFACEBASE_H
