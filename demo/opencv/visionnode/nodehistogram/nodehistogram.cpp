//
// Created by 25137 on 2026/11/15.
//

#include "nodehistogram.h"
#include "histogramitem.h"
#include "../visionconfigpage.h"
#include "cal/opencvQT.h"
NodeHistogram::NodeHistogram()
{
    m_outPorts.clear();
}
void NodeHistogram::setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex)
{
    NodeVisionBase::setInData(nodeData, portIndex);
    m_imageData = m_inData;
}

void NodeHistogram::_configInt()
{
    m_item = new HistogramItem();
    connect(m_item,&HistogramItem::cal,this,[this](HistogramItem::Type t1)
    {
        binNum = m_item->num();
        switch (t1)
        {
        case HistogramItem::RGB:
            rgb_cnt();
            break;
        case HistogramItem::COLOR:
            color_cnt();
            break;
        }
    });
    configPage()->setConfigPropertyItem(m_item);

}
void NodeHistogram::_configOpen()
{

    m_item->init();
    configPage()->showImage(m_imageData->images());
}
void NodeHistogram::_updateConfig()
{
    if (m_inData->images().size())
    {

    }
}
void NodeHistogram::color_cnt()
{

    auto src = QImageToCvMat(m_inData->images().at(0).second);

    cv::Mat colorHist;
    auto mask =cv::Mat();

    OpencvCal::getHistogram(src, colorHist, 0, binNum, false, mask, true);
    std::vector<std::pair<cv::Vec3b, float>> colorCountList;

    float binScale = 256.0f / binNum;
    typedef union
    {
        struct
        {
            uint8_t b:8;
            uint8_t g:8;
            uint8_t r:8;
            uint8_t a:8;
        }S;
        uint32_t v;
    }_C_;
    _C_ _color;
    auto d = m_item->data(HistogramItem::COLOR_PLOT);
    QCPGraphData value;
    d->clear();
    for (int b = 0; b < binNum; b++)
    {
        for (int g = 0; g < binNum; g++)
        {
            for (int r = 0; r < binNum; r++)
            {
                float cnt = colorHist.at<float>(b, g, r);
                if (cnt < 1e-6) continue;
                // bin中心代表色
                _color.S.b = static_cast<uchar>(b * binScale + binScale / 2);
                _color.S.g = static_cast<uchar>(g * binScale + binScale / 2);
                _color.S.r = static_cast<uchar>(r * binScale + binScale / 2);
                _color.S.a = 0;
                value.key = _color.v;
                value.value = cnt;
                d->add(value);
            }
        }
    }
}
void NodeHistogram::rgb_cnt()
{
    auto src = QImageToCvMat(m_inData->images().at(0).second);
    cv::Mat Bhist;
    QSharedPointer<QCPGraphDataContainer> d;
    QCPGraphData value;

    OpencvCal::getHistogram(src,Bhist,0);
    d = m_item->data(HistogramItem::B_PLOT);
    d->clear();
    for (int i = 0; i < Bhist.cols; ++i)
    {
        value.key = i;
        value.value = Bhist.at<float>(0, i);
        d->add(value);
    }
    d = m_item->data(HistogramItem::G_PLOT);
    d->clear();
    OpencvCal::getHistogram(src,Bhist,1);

    for (int i = 0; i < Bhist.cols; ++i)
    {
        value.key = i;
        value.value = Bhist.at<float>(0, i);
        d->add(value);
    }

    d = m_item->data(HistogramItem::R_PLOT);
    d->clear();
    OpencvCal::getHistogram(src,Bhist,2);
    for (int i = 0; i < Bhist.cols; ++i)
    {
        value.key = i;
        value.value = Bhist.at<float>(0, i);
        d->add(value);
    }
}
