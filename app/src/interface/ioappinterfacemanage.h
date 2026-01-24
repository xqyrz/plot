//
// Created by 25137 on 26-1-1.
//

#ifndef IOAPPINTERFACEMANAGE_H
#define IOAPPINTERFACEMANAGE_H
#include "../plug/ioapp/ioappinterface.h"
#include <QObject>

#include "manage.h"

class IOAPPInterfaceManage : public QObject ,public ManageBase {
    Q_OBJECT
public:
    static IOAPPInterfaceManage *instance();
    auto const& getPlugs() const { return plugs; }
    int addPlug(const QString& plugPath)
    {
        if (plugs.contains(plugPath)) return false;
        plugs.append(plugPath);
        return true;
    }
    QObject* creatObj(const BaseModel*  index,QString type) override;
    bool hasIndex(const BaseModel*  index)const override;
private:
    explicit IOAPPInterfaceManage(QObject *parent = nullptr);
    static IOAPPInterfaceManage* m_iOAPPInterfaceManage;



    Q_DISABLE_COPY(IOAPPInterfaceManage)
};



#endif //IOAPPINTERFACEMANAGE_H
