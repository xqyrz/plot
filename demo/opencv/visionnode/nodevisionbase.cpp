//
// Created by 25137 on 2026/11/8.
//

#include "nodevisionbase.h"
#include <QMenu>
#include <qmetaobject.h>

#include "imageLabel.h"
#include "visionconfigpage.h"
NodeVisionBase::NodeVisionBase()
    : NodeDelegateModel()
    , m_imageData(new ImageNodeData())
{
    m_inPorts.append(NodeDataType{"image","i"});
    m_outPorts.append(NodeDataType{"image","o"});

}
NodeVisionBase::~NodeVisionBase()
{
    if (m_imageItem)
    {
        m_imageItem->deleteLater();
    }
    if (m_configPage)
    {
        m_configPage->deleteLater();
    }
}

QList<std::pair<QString, QImage>> NodeVisionBase::images()
{
    return m_imageData->images();
}
unsigned int NodeVisionBase::nPorts(PortType portType) const
{
    unsigned int result = 0;
    switch (portType) {
        case PortType::In:return m_inPorts.size();
        case PortType::Out:return m_outPorts.size();
        default:break;
    }
    return result;
}
NodeDataType NodeVisionBase::dataType(PortType portType, PortIndex portIndex) const
{
    switch (portType) {
        case PortType::In:return m_inPorts.at(portIndex);
        case PortType::Out:return m_outPorts.at(portIndex);
        default:return {};
    }
}
std::shared_ptr<NodeData> NodeVisionBase::outData(PortIndex port)
{
    return m_imageData;
}
QWidget* NodeVisionBase::embeddedWidget()
{
    if (!m_imageItem) {
        m_imageItem = new ImageLabel();
        m_imageItem->setMinimumWidth(50);
        m_imageItem->setContextMenuPolicy(Qt::CustomContextMenu);


    }
    return m_imageItem;
}
void NodeVisionBase::showConfigPage()
{

    configPage()->show();
    _configOpen();
}

VisionConfigPage* NodeVisionBase::configPage()
{
    if (m_configPage == nullptr)
    {
        m_configPage = new VisionConfigPage();
        m_configPage->setTilt(property("tilt").toString());
        m_configPage->setType("节点类型: "+QString::fromUtf8(metaObject()->className()));
        m_configPage->setDesc(property("desc").toString());
        m_configPage->setHelp(property("help").toString());
        _configInt();
        connect(m_configPage,&VisionConfigPage::okClicked,this,&NodeVisionBase::_updateConfig);

    }
    return m_configPage;
}
