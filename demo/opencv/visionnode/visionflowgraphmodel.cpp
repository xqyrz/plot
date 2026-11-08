//
// Created by 25137 on 2026/11/8.
//

#include "visionflowgraphmodel.h"
#include "NodeVisionBase.h"
namespace QtNodes
{
    void VisionFlowGraphModel::showConfigPage(NodeId const nodeId)
    {
        auto& _models = models();
        auto node =static_cast<NodeVisionBase*>(_models.at(nodeId).get());
        qDebug()<<node;
        node->showConfigPage();
    }
}