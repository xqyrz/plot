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
using namespace QtNodes;
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
private:
    std::shared_ptr<NodeDelegateModelRegistry> registry;
    DataFlowGraphModel* dataFlowGraphModel=nullptr;
    DataFlowGraphicsScene* scene=nullptr;
};
#endif //NODEEDITPAGE_H
