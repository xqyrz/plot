//
// Created by 25137 on 2026/11/8.
//

#include "nodeaffinetransformation.h"
#include "affinetransformationitem.h"
#include "../visionconfigpage.h"
#include "cal/opencvQT.h"

nodeAffineTransformation::nodeAffineTransformation()
{
    setProperty("tilt","2D变换");
    setProperty("desc","投影，仿射，(放缩:scale(double),旋转rotate(double),移动move(x(double),y,z)");
    setProperty("help","可以配置变换矩阵参数");
}
nodeAffineTransformation::~nodeAffineTransformation()
{

}
void nodeAffineTransformation::setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex)
{
    auto data =static_cast<ImageNodeData*>(nodeData.get());

    m_inData->clear();
    auto images = data->images();
    //TODO:每一个节点是否要备份一份传入数据
    for (auto& image: images)
    {
        m_inData->setImage(image.first,image.second);
    }
    auto inImages = m_inData->images();
    for (auto& image: inImages)
    {

        QString name = "AT:"+image.first;
        auto m_image = image.second;
        OpencvCal cal;

        auto cvImage = QImageToCvMat(m_image);
        cv::Mat out;
        OpencvCal::Affine_Transformation(cvImage,cal.rotate(60,cvImage.size()),out);
        auto outImage = cvMatToQImage(out);
        m_imageData->setImage(name,outImage);
    }

}
void nodeAffineTransformation::_configInt()
{
    m_item = new AffineTransformationItem();

    configPage()->setConfigPropertyItem(m_item);
}
void nodeAffineTransformation::_configOpen()
{
    QString s;
    auto& images = m_inData->images();
    m_item->setMat(s,images.first().second.size());
    QList<std::pair<QString, QImage>> _images;
    for (auto & var:images)
    {
        auto cvImage = QImageToCvMat(var.second);
        cv::Mat out;
        auto m_M = m_item->M();
        cv::Mat mat(3, 3, CV_64F,m_M.data());
        OpencvCal::Affine_Transformation(cvImage,mat,out);
        _images.push_back(std::pair<QString, QImage>{});
        _images.last().first = var.first;
        _images.last().second = cvMatToQImage(out);
    }
    configPage()->showImage(_images);
}
void nodeAffineTransformation::_updateConfig()
{

}
