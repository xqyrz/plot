//
// Created by 25137 on 2026/10/19.
//

#ifndef PLOT_PLUGLOADER_H
#define PLOT_PLUGLOADER_H

#include <QPluginLoader>
class InterfaceBase;
class PlugLoader:public QPluginLoader
{
    public:
        PlugLoader(const QString &fileName, QObject *parent = nullptr);
    ~PlugLoader();
    QObject* P_interface();
    bool P_load();
    private:
    InterfaceBase* m_interface{};
};


#endif // PLOT_PLUGLOADER_H
