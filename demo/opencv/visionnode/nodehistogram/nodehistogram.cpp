//
// Created by 25137 on 2026/11/15.
//

#include "nodehistogram.h"
#include "plotview.h"
#include "../visionconfigpage.h"
NodeHistogram::NodeHistogram()
{
    m_outPorts.clear();
}
void NodeHistogram::setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex)
{

}
void NodeHistogram::_configInt()
{
    m_item = new PlotView();
    configPage()->setConfigPropertyItem(m_item->ui());
}
void NodeHistogram::_configOpen()
{

}
void NodeHistogram::_updateConfig()
{

}
