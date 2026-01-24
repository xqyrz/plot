//
// Created by 25137 on 26-1-11.
//

#ifndef MANAGE_H
#define MANAGE_H
#include <QSharedPointer>
#include <QMap>
#include "page/node/nodemodel.h"

class BaseModel;
namespace ManageData
{
    enum class  Type
    {
        Default,
        VIEW,
        IO,
        IOAPP,
        SIGNAL,
    };
}
class ManageBase{
public:
    virtual ~ManageBase()=default;
    virtual QString check(QString& var)const;
    virtual QObject* creatObj(const BaseModel* index,QString type)=0;
    virtual bool hasIndex(const BaseModel*  index)const=0;
     QObject* getObj(const BaseModel*  index)const {return objs.value(index);}
protected:
    ManageData::Type type=ManageData::Type::Default;
    QMap< const BaseModel* ,QObject*> objs;
    QList<QString> plugs;
};

class Manage {
public:
    static QObject* getObj(const BaseModel*  index);
    static QObject* creatObj(const BaseModel* index,QString type);
};



#endif //MANAGE_H
