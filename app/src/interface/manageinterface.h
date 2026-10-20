//
// Created by 25137 on 2026/10/10.
//

#ifndef PLOT_MANAGEINTERFACE_H
#define PLOT_MANAGEINTERFACE_H

#include <QObject>
#include "page/node/nodemodel.h"
class QPluginLoader;

 namespace QtNodes
{
    class NodeDelegateModelRegistry;
     class DataFlowGraphModel;

}
class PlugData{
public:
    QString fileName;
    QString name;
    QString date;
    PLUG::Type type;
    QList<PLUG::InputType> in;
    QList<PLUG::OutputType> out;
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
    Q_OBJECT
public:

   static ManageInterface* instance(QObject* parent=nullptr);
    virtual ~ManageInterface() = default;
    void addPlug( QPluginLoader* plug);
    QObject* getObj(const int  index)const {return nullptr;}
    const QList<PlugData>& getPlugs()const {return plugs;}
    QtNodes::DataFlowGraphModel* model()const{return dataFlowGraphModel;};
signals:
    void configClicked(BaseModel* node);
private:
    ManageInterface(QObject* parent);
    std::shared_ptr<QtNodes::NodeDelegateModelRegistry> _registerDataModels();
private:
    QList<PlugData> plugs;
    std::shared_ptr<QtNodes::NodeDelegateModelRegistry> m_registry;
    QtNodes::DataFlowGraphModel* dataFlowGraphModel;
};


#endif // PLOT_MANAGEINTERFACE_H
