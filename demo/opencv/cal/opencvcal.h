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


    /**
     * @brief 计算图像直方图
     * @param src       输入图像
     * @param hist      输出直方图，CV_32F
     * @param channel   通道索引，B=0, G=1, R=2
     * @param bins      直方图区间数量
     * @param normalize 是否归一化到 [0,1]
     * @param mask      可选掩码
     * @return          是否计算成功
     */
    static bool getHistogram(
        const cv::Mat& src,
        cv::Mat& hist,
        int channel = 0,
        int bins = 256,
        bool normalize = false,
        const cv::Mat& mask = cv::Mat()
    );


    static ImageLuminance getLuminance(const cv::Mat& src);
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
