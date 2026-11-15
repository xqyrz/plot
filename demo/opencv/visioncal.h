//
// Created by 25137 on 2026/10/25.
//

#ifndef PLOT_VSIONCAL_H
#define PLOT_VSIONCAL_H

#include <opencv2/opencv.hpp>
class VisionCal
{
public:
    virtual cv::Mat* currImage()=0;
    struct ImageLuminance
    {
        double y601 = 0.0;  // BT.601，范围 0~100
        double y709 = 0.0;  // BT.709，范围 0~100
        double lStar = 0.0; // CIE L*，范围 0~100
    };









    //CAL
    virtual bool Affine_Transformation(const cv::Mat& M,  cv::Mat& out){return false;};
    static cv::Mat composeMat( cv::Mat& M,const cv::Mat& T);
    static cv::Mat move( double x, double y,cv::Size& imgSize,cv::Mat M={});
    static cv::Mat rotate( double angle, cv::Size imgSize,cv::Mat M={});
    static cv::Mat scale( double sx, double sy, cv::Size& imgSize,cv::Mat M={});

};


#endif // PLOT_VSIONCAL_H
