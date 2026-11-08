//
// Created by 25137 on 2026/10/27.
//

#include "visioncalpage.h"

#include <QTimer>
#include <QtNodes/ConnectionStyle>
#include <QtNodes/DataFlowGraphModel>

#include <QtNodes/GraphicsView>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>


#include "visionnode/visionflowgraphicsscene.h"
#include "visionnode/visionflowgraphmodel.h"

#include "visionnode/nodeimage/NodeImage.hpp"
#include "visionnode/nodeAffineTransformation/nodeaffinetransformation.h"
static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();
    ret->registerModel<NodeImage>("Sources");
    ret->registerModel<nodeAffineTransformation>("CAL");
    return ret;
}

VisionCalPage::VisionCalPage(QWidget* parent)
    :GraphicsView(parent)
    ,m_model(new VisionFlowGraphModel(registerDataModels()))
    ,m_scene(new VisionFlowGraphicsScene(*m_model))
{
    m_scene->setConfigName("vision");

    this->setScene(m_scene);
    auto _updata = [this](NodeId const id)
    {
        auto model =m_model->nodeData(id,NodeRole::PlugPtr).value<NodeVisionBase*>();
        emit updateImage(model->images());
    };

    connect(m_model,&DataFlowGraphModel::configClicked,this,_updata);
    connect(m_scene,&DataFlowGraphicsScene::nodeSelected,this,_updata);

   // connect(m_scene,&DataFlowGraphicsScene::up,this,_updata);
    QTimer::singleShot(1,this,[this]()
    {
        m_scene->load(m_scene->configName());
    });
}
