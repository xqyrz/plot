//
// Created by 25137 on 25-12-16.
//

#ifndef NODEEDITPAGE_H
#define NODEEDITPAGE_H



#include <QtNodes/ConnectionStyle>
#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>
class InterfaceBase;
using namespace QtNodes;
class IOInterface_obj;
class NodeEditPage : public GraphicsView
{
    Q_OBJECT
public:
    NodeEditPage(QWidget *parent = Q_NULLPTR);
    signals:
    void d(int);
private:
    static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels();
    void _sceneLoaded();
    void showConfigDialog(QObject* obj,int index);
    void _saveConfig(const int index,const QList<std::tuple<QVariant::Type,QString,QVariant>>& config);
    QList<int> _allIndexes() const;
    QList<std::tuple<QVariant::Type, QString, QVariant>> _loadConfig(int index);
private:
    std::shared_ptr<NodeDelegateModelRegistry> registry;
    DataFlowGraphModel* dataFlowGraphModel=nullptr;
    DataFlowGraphicsScene* scene=nullptr;
    const QString configPath;
};
#endif //NODEEDITPAGE_H
