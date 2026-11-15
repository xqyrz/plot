//
// Created by 25137 on 2026/11/14.
//

#include "nodegamma.h"

#include "../visionconfigpage.h"
#include "visionnode/imageLabel.h"
#include "gammaitem.h"

#include "cal/opencvQT.h"
void NodeGamma::setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex)
{
    NodeVisionBase::setInData(nodeData, portIndex);

    if (m_inData->images().size())
    {
        auto src = QImageToCvMat(m_inData->images().at(0).second);
        if (_lut.size()==0)
        {

            OpencvCal::gammaLut(src,gammaVlaue,_lut);
        }
        cv::Mat out;
        OpencvCal::Lut_Cal(src,_lut,out);
        auto outImage = cvMatToQImage(out);
       // outImage.save("outImage.png");
        m_imageData->setImage(m_inData->images().at(0).first,outImage);
        auto ret=OpencvCal::getLuminance(out);
        m_imageItem->setText(
                QString("%1,%2,%3").arg(ret.lStar).arg(ret.y601).arg(ret.y709));
    }

}
void NodeGamma::_configInt()
{
    m_item = new GammaItem();
    m_item->setLut(&_lut);
    connect(m_item,&GammaItem::lutCreate,this,[this](double value)
    {
        gammaVlaue = value;
        if (m_inData->images().size())
        {
            auto src = QImageToCvMat(m_inData->images().at(0).second);
            OpencvCal::gammaLut(src,gammaVlaue,_lut);
            m_item->setLut(&_lut);
        }
    });
    connect(m_item,&GammaItem::updatePlot,this,[this]()
    {
        if (m_inData->images().size())
        {
            auto src = QImageToCvMat(m_inData->images().at(0).second);
            cv::Mat out;
             OpencvCal::Lut_Cal(src,_lut,out);
            auto outImage = cvMatToQImage(out);
            m_imageData->setImage(m_inData->images().at(0).first,outImage);
            auto ret=OpencvCal::getLuminance(out);
            m_item->setText(
                QString("%1,%2,%3").arg(ret.lStar).arg(ret.y601).arg(ret.y709));
        }
        _updateConfig();
    });
    configPage()->setConfigPropertyItem(m_item);
}
void NodeGamma::_configOpen()
{
    configPage()->showImage(m_imageData->images());
    emit m_item->updatePlot();
}
void NodeGamma::_updateConfig()
{
    configPage()->showImage(m_imageData->images());
}
