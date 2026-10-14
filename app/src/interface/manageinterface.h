//
// Created by 25137 on 2026/10/10.
//

#ifndef PLOT_MANAGEINTERFACE_H
#define PLOT_MANAGEINTERFACE_H

#include <QObject>
#include "page/node/nodemodel.h"
class QPluginLoader;
class PlugData{
public:
    QString fileName;
    QString name;
    QString date;
    Plug::Type type;
    QList<Plug::InputType> in;
    QList<Plug::OutputType> out;
    bool operator==(const PlugData& other) const
    {
        return other.fileName == fileName;
    }
    PlugData& operator=(const PlugData& other)
    {
        if (this != &other)
        {
            fileName = other.fileName;
            name = other.name;
            date = other.date;
            type = other.type;
            in = other.in;
            out = other.out;
        }
        return *this;
    }
};
class ManageInterface:public QObject
{
public:

   static ManageInterface* instance(QObject* parent=nullptr);
    virtual ~ManageInterface() = default;
    void addPlug(const QPluginLoader* plug);
    QObject* getObj(const int  index)const {return nullptr;}
private:
    ManageInterface(QObject* parent);
private:
    QList<PlugData> plugs;
};


#endif // PLOT_MANAGEINTERFACE_H
