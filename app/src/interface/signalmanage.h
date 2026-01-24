//
// Created by 25137 on 26-1-10.
//

#ifndef SIGNALMANAGE_H
#define SIGNALMANAGE_H


#include "obj/signalobj.h"
#include <QSharedPointer>
#include "manage.h"
class SignalManage : public QObject ,public ManageBase
{
public:


    static SignalManage *instance(QObject* parent=nullptr);
    QString check(QString& var) const override;
    QObject* creatObj(const BaseModel*  index, QString type)override;
    bool hasIndex(const BaseModel*  index) const override{ return objs.keys().contains(index); }
    bool addId(    uint outNodeId,
    uint outPortIndex,
    uint inNodeId,
    uint inPortIndex);
    auto const & getIds()const{return ids;};

private:
    SignalManage(QObject* parent = nullptr) : QObject(parent) {};

private:

    static SignalManage* m_SignalManage;
    QList<std::tuple<uint,uint,uint,uint>> ids;
};



#endif //SIGNALMANAGE_H
