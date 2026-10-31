//
// Created by 25137 on 2026/10/25.
//

#include "opencvcal.h"
#include <opencv2/geometry.hpp>   // OpenCV 5.x: getAffineTransform 在这
#include <opencv2/imgproc.hpp>    // warpAffine 还在这
cv::Mat* OpencvCal::currImage()
{
    std::string path = "rec/image/chess.bmp";
    m_currImage = cv::imread(path, cv::IMREAD_COLOR);
    return &m_currImage;
}
OpencvCal::OpencvCal()

{
    std::string path = "rec/image/chess.bmp";
   m_currImage = cv::imread(path, cv::IMREAD_COLOR);
}
bool OpencvCal::Affine_Transformation(const cv::Mat& src, const cv::Mat& M,  cv::Mat& out)
{
    // 空图 / 矩阵不合法 直接返回失败
    if (src.empty() || M.empty() || M.rows != 3 || M.cols != 3)
        return false;
    cv::Mat M2x3 = M(cv::Rect(0, 0, 3, 2)).clone();
    try
    {
        // 输出尺寸默认与原图一致
        //cv::warpAffine
        cv::warpPerspective(src, out, M, src.size(),
                       cv::INTER_LINEAR,        // 双线性插值
                       cv::BORDER_CONSTANT,     // 边界常量填充
                       cv::Scalar(0, 0, 0));    // 填充黑色
        return !out.empty();
    }
    catch (const cv::Exception& e)
    {
        // OpenCV 异常时返回失败
        std::cerr << "Affine_Transformation failed: " << e.what() << std::endl;
        return false;
    }
}
bool OpencvCal::Affine_Transformation(const cv::Mat& M, cv::Mat& out)
{
    return Affine_Transformation(*currImage(),M, out);
}
