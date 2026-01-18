//
// Created by 25137 on 26-1-11.
//

#ifndef MANAGE_H
#define MANAGE_H
#include <QSharedPointer>
#include <QMap>
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
    virtual bool creatObj(int index,QString type)=0;
    virtual bool hasIndex(int index)const=0;
     QObject* getObj(int index)const {return objs.value(index);}
protected:
    ManageData::Type type=ManageData::Type::Default;
    QMap< int,QObject*> objs;
    QList<QString> plugs;
};

class Manage {
public:
    static QObject* getObj(int index);
};



#endif //MANAGE_H
