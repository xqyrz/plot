//
// Created by 25137 on 26-2-10.
//

#ifndef PAGEBASE_H
#define PAGEBASE_H

#include "../interfacebase.h"
#include <QDebug>

class PageBase:public InterfaceBase {
Q_OBJECT

public:
    using InterfaceBase::InterfaceBase;

         QWidget* ui(){return _ui;};
protected:
    inline static const  QString KEY =QStringLiteral("key");
    inline static const  QString CONFIG_KEY =QStringLiteral("config");
protected:
    QWidget* _ui{nullptr};
};

QT_BEGIN_NAMESPACE
#define PageBase_Id "VIEW.Plugin.Base"
Q_DECLARE_INTERFACE(PageBase, PageBase_Id);
QT_END_NAMESPACE


#endif //PAGEBASE_H
