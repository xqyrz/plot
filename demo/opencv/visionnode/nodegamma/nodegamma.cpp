//
// Created by 25137 on 2026/11/14.
//

#include "nodegamma.h"

#include "../visionconfigpage.h"

#include "gammaitem.h"

#include "cal/opencvQT.h"
void NodeGamma::setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex)
{
    NodeVisionBase::setInData(nodeData, portIndex);
   auto src = QImageToCvMat(m_inData->images().at(0).second);
   OpencvCal::gammaLut(src,2.2,_lut);

}
void NodeGamma::_configInt()
{
    m_item = new GammaItem();
    m_item->setLut(&_lut);
    configPage()->setConfigPropertyItem(m_item);
}
void NodeGamma::_configOpen() {}
void NodeGamma::_updateConfig() {}
