//
// Created by 25137 on 2026/11/15.
//

#include "nodehistogram.h"
#include "histogramitem.h"
#include "../visionconfigpage.h"
#include "cal/opencvQT.h"
#include <opencv2/imgproc.hpp>   // calcHist / cvtColor
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
        case HistogramItem::BT601:
            luminance_cnt();
            break;
        case HistogramItem::HSV:
            hsv_cnt();
            break;
        case HistogramItem::HLS:
            hls_cnt();
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
    if (!m_inData || m_inData->images().empty())
        return;

    auto src = QImageToCvMat(m_inData->images().at(0).second);
    if (src.empty())
        return;

    cv::Mat colorHist;
    auto mask =cv::Mat();

    if (!OpencvCal::getHistogram(src, colorHist, 0, binNum, false, mask, true))
        return;
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
    if (!m_inData || m_inData->images().empty())
        return;

    auto src = QImageToCvMat(m_inData->images().at(0).second);
    if (src.empty())
        return;

    QSharedPointer<QCPGraphDataContainer> d;
    QCPGraphData value;
    const float binScale = 256.0f / binNum;

    // B / G / R 三个通道统一用 binNum 统计，横轴统一用 bin 中心亮度值
    const int channels[3] = {0, 1, 2};
    const HistogramItem::PlotEnum plots[3] = {
        HistogramItem::B_PLOT,
        HistogramItem::G_PLOT,
        HistogramItem::R_PLOT
    };

    for (int c = 0; c < 3; ++c)
    {
        cv::Mat hist;
        if (!OpencvCal::getHistogram(src, hist, channels[c], binNum, false))
            continue;

        d = m_item->data(plots[c]);
        d->clear();
        for (int i = 0; i < hist.cols; ++i)
        {
            value.key = i * binScale + binScale / 2.0f;
            value.value = hist.at<float>(0, i);
            d->add(value);
        }
    }
}

void NodeHistogram::luminance_cnt()
{
    if (!m_inData || m_inData->images().empty())
        return;
    float _binNum=256.0f;
    auto src = QImageToCvMat(m_inData->images().at(0).second);
    if (src.empty())
        return;

    cv::Mat lumaHist;
    // BT.601：内部先 cvtColor 成 Y，再做一维直方图
    if (!OpencvCal::getLuminanceHistogram(src, lumaHist, _binNum, false))
    {
        qWarning() << "luminance_cnt failed";
        return;
    }

    auto d = m_item->data(HistogramItem::L_PLOT);
    d->clear();

    // 横轴用亮度值（bin 中心），范围 0~255，比用 bin 索引更直观
    const float binScale = 256.0f / _binNum;
    QCPGraphData value;
    qDebug()<<"lumaHist"<<lumaHist.channels();
    for (int i = 0; i < lumaHist.cols; ++i)
    {
        value.key = i * binScale + binScale / 2.0f;
        value.value = lumaHist.at<float>(0, i);
        d->add(value);
    }
}

namespace
{
// 统计指定通道的一维直方图。
// H 通道范围是 0~180，S/V/L 是 0~256，不能直接用 OpencvCal::getHistogram（它固定按 0~256）
bool calcChannelHist(const cv::Mat& src, int channel, int bins, float maxRange, cv::Mat& hist)
{
    hist.release();
    if (src.empty() || bins <= 0 || channel < 0 || channel >= src.channels())
        return false;

    int channels[] = {channel};
    int histSize[] = {bins};
    float range[] = {0.0f, maxRange};
    const float* ranges[] = {range};

    cv::calcHist(&src, 1, channels, cv::Mat(), hist, 1, histSize, ranges);
    return !hist.empty();
}

// 把一维直方图灌进曲线：横轴统一用 0~360 刻度，
// H 的 bin 中心 ×(360/180) 后正好是真实色相角度（0~360°），
// S / V / L 则是"占满量程的百分比 ×360"，三条曲线共用一条坐标轴、量程一致可横向比较
void fillPlotData(HistogramItem* item, HistogramItem::PlotEnum plot, const cv::Mat& hist)
{
    auto d = item->data(plot);
    if (!d)
        return;

    d->clear();
    const int n = static_cast<int>(hist.total());
    if (n <= 0)
        return;

    QCPGraphData value;
    for (int i = 0; i < n; ++i)
    {
        value.key = (i + 0.5) / n * 360.0;   // 0~360（度）
        value.value = hist.at<float>(i);
        d->add(value);
    }
}
}

void NodeHistogram::hsv_cnt()
{
    if (!m_inData || m_inData->images().empty())
        return;

    auto src = QImageToCvMat(m_inData->images().at(0).second);   // 8UC3 BGR
    if (src.empty() || src.channels() != 3 || src.depth() != CV_8U)
    {
        qWarning() << "hsv_cnt: unsupported image";
        return;
    }

    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);   // H∈[0,180)，S/V∈[0,256)

    cv::Mat hHist, sHist, vHist;
    if (!calcChannelHist(hsv, 0, binNum, 180.0f, hHist) ||
        !calcChannelHist(hsv, 1, binNum, 256.0f, sHist) ||
        !calcChannelHist(hsv, 2, binNum, 256.0f, vHist))
    {
        qWarning() << "hsv_cnt failed";
        return;
    }

    fillPlotData(m_item, HistogramItem::HSV_H_PLOT, hHist);
    fillPlotData(m_item, HistogramItem::HSV_S_PLOT, sHist);
    fillPlotData(m_item, HistogramItem::HSV_V_PLOT, vHist);
}

void NodeHistogram::hls_cnt()
{
    if (!m_inData || m_inData->images().empty())
        return;

    auto src = QImageToCvMat(m_inData->images().at(0).second);   // 8UC3 BGR
    if (src.empty() || src.channels() != 3 || src.depth() != CV_8U)
    {
        qWarning() << "hls_cnt: unsupported image";
        return;
    }

    cv::Mat hls;
    cv::cvtColor(src, hls, cv::COLOR_BGR2HLS);   // H∈[0,180)，L/S∈[0,256)

    cv::Mat hHist, lHist, sHist;
    if (!calcChannelHist(hls, 0, binNum, 180.0f, hHist) ||
        !calcChannelHist(hls, 1, binNum, 256.0f, lHist) ||
        !calcChannelHist(hls, 2, binNum, 256.0f, sHist))
    {
        qWarning() << "hls_cnt failed";
        return;
    }

    fillPlotData(m_item, HistogramItem::HLS_H_PLOT, hHist);
    fillPlotData(m_item, HistogramItem::HLS_L_PLOT, lHist);
    fillPlotData(m_item, HistogramItem::HLS_S_PLOT, sHist);
}
