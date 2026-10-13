//
// Created by 25137 on 26-1-11.
//

#ifndef MANAGE_H
#define MANAGE_H
#include <QSharedPointer>
#include <QMap>
#include "page/node/nodemodel.h"

class BaseModel;
class InterfaceBase;

class ManageBase{
public:

    virtual ~ManageBase()=default;
    virtual QString check(QString& var)const;
    virtual QObject* creatObj(const int index,QString type)=0;
    virtual bool hasIndex(const int  index)const=0;
     QObject* getObj(const int  index)const {return objs.value(index);}
    QMap<  int ,QObject*> getObjs(){return objs;};
    int addPlug(const QString& plugPath)
    {
       // if (plugs.contains(plugPath)) return false;
       // plugs.append(plugPath);
        return true;
    }
protected:
    Plug::Type type=Plug::Type::Default;
    QMap<  int ,QObject*> objs;
    QList<QString> plugs;
};

class Manage {
public:
    static QObject* getObj(const int  index);
    static InterfaceBase* getInterfaceBase(const int  index);
    static QObject* creatObj(const int index,QString type);
    static void showConfig(const int  index);
};



#endif //MANAGE_H
