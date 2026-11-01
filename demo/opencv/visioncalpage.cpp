//
// Created by 25137 on 2026/10/27.
//

#include "visioncalpage.h"
#include <QtNodes/ConnectionStyle>
#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>

#include "nodeimage.hpp"
static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();
    ret->registerModel<NodeImage>("Sources");

    return ret;
}

VisionCalPage::VisionCalPage(QWidget* parent)
    :GraphicsView(parent)
    ,m_model(new DataFlowGraphModel(registerDataModels()))
    ,m_scene(new DataFlowGraphicsScene(*m_model))
{

    this->setScene(m_scene);
    connect(m_scene,&DataFlowGraphicsScene::nodeClicked,this,[this](NodeId const id)
    {
        auto model =m_model->nodeData(id,NodeRole::PlugPtr).value<NodeImage*>();
        emit updateImage(model->images());
        qDebug()<<model;
    });
}
