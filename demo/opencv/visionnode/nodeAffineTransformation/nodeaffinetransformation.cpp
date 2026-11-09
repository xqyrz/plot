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
    cv::Mat _M =cv::Mat::eye(3, 3, CV_64FC1);
    std::copy_n(M.begin(), 9,_M.ptr<double>());
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
        cv::Mat MM =cv::Mat::eye(3, 3, CV_64FC1);
        std::copy_n(MM.ptr<double>(), 9,M.begin());
        OpencvCal::Affine_Transformation(cvImage,MM,out);
        auto outImage = cvMatToQImage(out);
        m_imageData->setImage(name,outImage);
    }

}
void nodeAffineTransformation::setM(std::array<double, 9> _M)
{
    M =_M;
    _updateConfig();
}
void nodeAffineTransformation::_configInt()
{
    m_item = new AffineTransformationItem();
    connect(m_item,&AffineTransformationItem::mChanged,this,[this]()
    {
        setM(m_item->M());
    });
    configPage()->setConfigPropertyItem(m_item);
}
void nodeAffineTransformation::_configOpen()
{
    QString s;
    auto& images = m_inData->images();
    m_item->setMat(s,images.first().second.size());
    QList<std::pair<QString, QImage>> _images;
    m_imageData->clear();
    for (auto & var:images)
    {
        auto cvImage = QImageToCvMat(var.second);
        cv::Mat out;
        auto m_M = m_item->M();
        cv::Mat mat(3, 3, CV_64F,m_M.data());
        OpencvCal::Affine_Transformation(cvImage,mat,out);
        _images.push_back(std::pair<QString, QImage>{});
        auto image = cvMatToQImage(out);
        m_imageData->setImage(var.first,image);
    }
    configPage()->showImage(m_imageData->images());
}
void nodeAffineTransformation::_updateConfig()
{
    cv::Mat out;
    cv::Mat MM =cv::Mat::eye(3, 3, CV_64FC1);
    std::copy_n(M.begin() , 9,MM.ptr<double>());
    if ( m_inData->images().isEmpty())return;
    QList<std::pair<QString, QImage>> _images;
    m_imageData->clear();
    for (auto&var:m_inData->images())
    {
        auto  image = QImageToCvMat( var.second);
        OpencvCal::Affine_Transformation(image,MM,out);
        auto outimage = cvMatToQImage(out);
        m_imageData->setImage(var.first,outimage);
    }
    if(configPage()->isVisible())  configPage()->showImage(m_imageData->images());
    Q_EMIT dataUpdated(0);
}
