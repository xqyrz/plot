//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_OPENCVQT_H
#define PLOT_OPENCVQT_H
#include "opencvcal.h"
#include <QImage>
#include <QDebug>
// 如果 copy = true，深拷贝，安全可写
inline cv::Mat QImageToCvMat(const QImage &src, bool copy = false)
{
    if (src.isNull())
        return {};

    QImage img;
    // 统一转到 RGB888，减少分支
    if (src.format() != QImage::Format_RGB888)
    {
        img = src.convertToFormat(QImage::Format_RGB888);
    }
    else
    {
        img = src;
    }

    cv::Mat mat(cv::Size(img.width(), img.height()),
                CV_8UC3,
                const_cast<uchar*>(img.bits()),
                img.bytesPerLine());

    cv::Mat bgr;
    cv::cvtColor(copy ? mat.clone() : mat, bgr, cv::COLOR_RGB2BGR);
    return bgr;
}
inline QImage cvMatToQImage(const cv::Mat &inMat)
{
    if (inMat.empty())
        return QImage();

    switch (inMat.type())
    {
    case CV_8UC3:
    {
        cv::Mat rgb;
        cv::cvtColor(inMat, rgb, cv::COLOR_BGR2RGB);
        QImage img(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
        return img.copy();
    }
    case CV_8UC4:
    {
        cv::Mat rgba;
        cv::cvtColor(inMat, rgba, cv::COLOR_BGRA2RGBA);
        QImage img(rgba.data, rgba.cols, rgba.rows, rgba.step, QImage::Format_RGBA8888);
        return img.copy();
    }
    case CV_8UC1:
    {
        QImage img(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Grayscale8);
        return img.copy();
    }
    default:
        qWarning() << "unsupported cv::Mat type:" << inMat.type();
        return QImage();
    }
}
#endif // PLOT_OPENCVQT_H
