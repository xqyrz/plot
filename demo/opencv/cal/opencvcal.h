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

    static bool getHistogram(const cv::Mat& src, cv::Mat& hist, int channel, int bins, bool normalize,
                      const cv::Mat& mask, bool multiColor);

    /**
     * @brief 转成亮度图（单通道）
     * @param src   BGR/BGRA/灰度图，支持 CV_8U、CV_16U、CV_32F
     * @param gray  输出单通道亮度图，与 src 同尺寸同深度
     * @return      是否成功
     * @note 采用 BT.601 权重 Y = 0.114B + 0.587G + 0.299R（即 cv::COLOR_BGR2GRAY）
     */
    static bool toLuminance(const cv::Mat& src, cv::Mat& gray);

    /**
     * @brief 亮度直方图（彩色图先转 Y 再统计，不是按 B/G/R 通道统计）
     * @param src       输入图像（彩色自动转亮度，灰度直接用）
     * @param hist      输出直方图，CV_32F
     * @param bins      区间数量（8U 通常 256，16U 通常 256/1024/65536）
     * @param normalize 是否归一化到占比
     * @param mask      可选掩码，尺寸必须与 src 一致
     * @return          是否成功
     */
    static bool getLuminanceHistogram(
        const cv::Mat& src,
        cv::Mat& hist,
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
