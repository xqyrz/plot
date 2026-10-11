//
// Created by 25137 on 2026/10/10.
//

#ifndef PLOT_MANAGEINTERFACE_H
#define PLOT_MANAGEINTERFACE_H

#include <QObject>
class ManageInterface:public QObject
{
public:
    ManageInterface* instance(QObject* parent=nullptr);
    virtual ~ManageInterface() = default;
private:
    ManageInterface(QObject* parent);
};


#endif // PLOT_MANAGEINTERFACE_H
