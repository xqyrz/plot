//
// Created by 25137 on 26-1-2.
//

#ifndef VIEWMANAGE_H
#define VIEWMANAGE_H
#include "manage.h"
class VIEWManage: public QObject ,public ManageBase {
    Q_OBJECT
public:
    static VIEWManage *instance(QObject* parent=nullptr);
    static bool hasType(const QString &type);
    static BaseModel creatType(const QString &type);
    QString check(QString& var)const override;
    QObject* creatObj(const int  index,QString type) override;
    bool hasIndex(const int  index)const override;
private:
    explicit VIEWManage(QObject *parent = nullptr);
    static VIEWManage* m_viewManage;

    Q_DISABLE_COPY(VIEWManage)
};



#endif //VIEWMANAGE_H
