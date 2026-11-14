//
// Created by 25137 on 2026/10/25.
//

#ifndef PLOT_OPENCVCAL_H
#define PLOT_OPENCVCAL_H

#include "../visioncal.h"
class OpencvCal:public VisionCal
{
public:
    OpencvCal();
     cv::Mat* currImage() override;

    static  bool gammaLut(const int maxValue,const double gamma,std::vector<uint16_t>& table);
    static  bool gammaLut(const cv::Mat& src,const double gamma,std::vector<uint16_t>& table);
    static  bool Gamma_Cal(const cv::Mat& src,const double gamma,  cv::Mat& out);
    static int maxValue(const cv::Mat& src);
    static bool Lut_Cal(const cv::Mat& src,const std::vector<uint16_t>& lut,  cv::Mat& out);
  //  static  bool Gamma_Cal(const cv::Mat& src,const std::vector<uint16_t>& lut,  cv::Mat& out);
    static  bool Affine_Transformation(const cv::Mat& src,const cv::Mat& M,  cv::Mat& out);
    bool Affine_Transformation(const cv::Mat& M,  cv::Mat& out) override;
private:
    cv::Mat m_currImage;
};


#endif // PLOT_OPENCVCAL_H
