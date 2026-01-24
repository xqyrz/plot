//
// Created by 25137 on 26-1-1.
//

#ifndef IOINTERFACEMANAGE_H
#define IOINTERFACEMANAGE_H

#include "../plug/io/iointerface.h"
#include <QPluginLoader>
#include "manage.h"

class IOInterfaceManage : public QObject,public ManageBase
{
    Q_OBJECT
public:
    static IOInterfaceManage *instance();
    auto const& getPlugs() const { return plugs; }
    int addPlug(const QString& plugPath)
    {
        if (plugs.contains(plugPath)) return false;
        plugs.append(plugPath);
        return true;
    }
    QString check(QString& var)const override;
    QObject* creatObj(const BaseModel*  index,QString type) override;
    bool hasIndex(const BaseModel*  index)const override;
private:
    explicit IOInterfaceManage(QObject *parent = nullptr);
    static IOInterfaceManage* m_iOInterfaceManage;
    QList<QString> plugs;
    QMap<const BaseModel* , QObject*> objs;

    Q_DISABLE_COPY(IOInterfaceManage)
};


#endif //IOINTERFACEMANAGE_H
