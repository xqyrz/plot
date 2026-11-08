//
// Created by 25137 on 2026/10/25.
//

#include "visioncal.h"
cv::Mat VisionCal::move( double x, double y, cv::Size& imgSize,cv::Mat M)
{
    if (M.empty() || M.rows != 3 || M.cols != 3)
        M = cv::Mat::eye(3, 3, CV_64F);

    // 3x3 平移矩阵 T
    cv::Mat T = (cv::Mat_<double>(3,3) <<
        1, 0, x,
        0, 1, y,
        0, 0, 1);
    return composeMat(M, T);
}

cv::Mat VisionCal::rotate( double angle, cv::Size imgSize,cv::Mat M)
{
    if (M.empty())
        M = cv::Mat::eye(3, 3, CV_64F);

    double cx = imgSize.width  / 2.0;
    double cy = imgSize.height / 2.0;
    double a  = angle * CV_PI / 180.0;   // 转弧度
    double ca = cos(a), sa = sin(a);

    // 绕中心旋转 3x3：T(center) * R * T(-center)
    cv::Mat R = (cv::Mat_<double>(3,3) <<
         ca, -sa,  cx - cx*ca + cy*sa,
         sa,  ca,  cy - cx*sa - cy*ca,
          0,   0,  1);
    return composeMat(M, R);
}

cv::Mat VisionCal::scale( double sx, double sy, cv::Size& imgSize,cv::Mat M)
{
    if (M.empty())
        M = cv::Mat::eye(3, 3, CV_64F);

    double cx = imgSize.width  / 2.0;
    double cy = imgSize.height / 2.0;
#if 1
    // 绕中心缩放 3x3
    cv::Mat S = (cv::Mat_<double>(3,3) <<
        sx,  0,  cx * (1 - sx),//中心位置不变
        0,  sy,  cy * (1 - sy),
        0,   0,  1);
#else
    // 绕中心缩放 3x3
    cv::Mat S = (cv::Mat_<double>(3,3) <<
        sx,  0,  0,//中心位置不变
        0,  sy,  0,
        0,   0,  1);
#endif
    return composeMat(M, S);
}

cv::Mat  VisionCal::composeMat(cv::Mat& M, const cv::Mat& T)
{
    if (M.empty())
        M = cv::Mat::eye(3, 3, CV_64F);   // 参数赋3x3恒等

    if ( T.empty()  || T.rows != 3 || T.cols != 3)
        return M;

    M = T * M;      // 3x3 直接乘法复合
    return M;
}
