#pragma once

#include "BasicGraphicsScene.hpp"
#include "DataFlowGraphModel.hpp"
#include "Export.hpp"
#include <QStandardPaths>
namespace QtNodes {

/**
 * @brief An advanced scene working with data-propagating graphs.
 *
 * The class represents a scene that existed in v2.x but built wit the
 * new model-view approach in mind.
 */
class NODE_EDITOR_PUBLIC DataFlowGraphicsScene : public BasicGraphicsScene
{
    Q_OBJECT
public:
    DataFlowGraphicsScene(DataFlowGraphModel &graphModel, QObject *parent = nullptr);
    ~DataFlowGraphicsScene() = default;

public:
    std::vector<NodeId> selectedNodes() const;
    QMenu *createSceneMenu(QPointF const scenePos) override;
    QString getDefaultConfigPath(){return defaultConfigPath;}
    const DataFlowGraphModel & getGraphModel(){return _graphModel;}
public Q_SLOTS:
    bool load(QString file);
private Q_SLOTS:
    bool _save()const;
    bool _export() const;
    bool _load();

Q_SIGNALS:
    void sceneLoaded();

private:
    DataFlowGraphModel &_graphModel;
    QAction* saveAction;
    QAction* exportAction;
    QAction* loadAction;
    const QString defaultConfigPath =  QStandardPaths::writableLocation(
                QStandardPaths::AppConfigLocation
            )+"/default.flow";
};

} // namespace QtNodes
