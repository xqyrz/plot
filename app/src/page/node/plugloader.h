//
// Created by 25137 on 2026/10/19.
//

#ifndef PLOT_PLUGLOADER_H
#define PLOT_PLUGLOADER_H

#include <QPluginLoader>
class PlugLoader:public QPluginLoader
{
    public:
        PlugLoader(const QString &fileName, QObject *parent = nullptr);
};


#endif // PLOT_PLUGLOADER_H
