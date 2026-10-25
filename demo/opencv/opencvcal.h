//
// Created by 25137 on 2026/10/25.
//

#ifndef PLOT_OPENCVCAL_H
#define PLOT_OPENCVCAL_H

#include "visioncal.h"
class OpencvCal:public VisionCal
{
public:
    OpencvCal();
     cv::Mat* currImage() override;



    static  bool Affine_Transformation(const cv::Mat& src,const cv::Mat& M,  cv::Mat& out);
    bool Affine_Transformation(const cv::Mat& M,  cv::Mat& out) override;
private:
    cv::Mat m_currImage;
};


#endif // PLOT_OPENCVCAL_H
