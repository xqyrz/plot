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
class BaseModel;
using namespace QtNodes;
class NodeEditPage : public GraphicsView
{
    Q_OBJECT
public:
    NodeEditPage(QWidget *parent = Q_NULLPTR);
    signals:
    void d(int);
private:
    static std::shared_ptr<NodeDelegateModelRegistry> _registerDataModels();
    void showConfigDialog(BaseModel* node);
    void _sceneLoaded();

    void _saveConfig(const int index,const QList<std::tuple<QVariant::Type,QString,QVariant>>& config);
    QList<int> _allIndexes() const;
    QList<std::tuple<QVariant::Type, QString, QVariant>> _loadConfig(int index);
private:
    DataFlowGraphicsScene* scene=nullptr;
    const QString configPath;
};
#endif //NODEEDITPAGE_H
