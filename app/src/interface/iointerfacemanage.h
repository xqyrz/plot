//
// Created by 25137 on 26-1-1.
//

#ifndef IOINTERFACEMANAGE_H
#define IOINTERFACEMANAGE_H

#include "../plug/io/iointerface.h"
#include <QPluginLoader>

#include <QObject>

class IOInterfaceManage : public QObject
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
    QString check(QString& var)const;
    bool creatObj(int index,QString type);
    bool hasIndex(int index)const;
    QObject* getObj(int index)const;
private:
    explicit IOInterfaceManage(QObject *parent = nullptr);
    static IOInterfaceManage* m_iOInterfaceManage;
    QList<QString> plugs;
    QMap<int, QObject*> objs;

    Q_DISABLE_COPY(IOInterfaceManage)
};


#endif //IOINTERFACEMANAGE_H
