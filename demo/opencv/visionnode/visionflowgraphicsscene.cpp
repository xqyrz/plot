//
// Created by 25137 on 2026/11/8.
//

#include "visionflowgraphicsscene.h"
#include "visionflowgraphmodel.h"
#include <QDebug>
namespace QtNodes
{
    VisionFlowGraphicsScene::VisionFlowGraphicsScene(VisionFlowGraphModel& graphModel, QObject* parent)
        :DataFlowGraphicsScene(graphModel,parent)
    {
        _init();
    }
    void VisionFlowGraphicsScene::_init()
    {
        connect(this,&DataFlowGraphicsScene::nodeDoubleClicked,this,[this](NodeId const id)
        {
             auto &  m_graphModel = static_cast< VisionFlowGraphModel & >(graphModel());
            m_graphModel.showConfigPage(id);
        });
    }
}