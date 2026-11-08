//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_VISIONFLOWGRAPHMODEL_H
#define PLOT_VISIONFLOWGRAPHMODEL_H

#include <QtNodes/DataFlowGraphModel>

namespace QtNodes
{
    class VisionFlowGraphModel:public DataFlowGraphModel
    {
        Q_OBJECT
    public:
        using DataFlowGraphModel::DataFlowGraphModel;
        void showConfigPage(NodeId const nodeId);
    };
}

#endif // PLOT_VISIONFLOWGRAPHMODEL_H
