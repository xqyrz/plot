//
// Created by 25137 on 2026/10/25.
//

#include "opencvcal.h"
#include <opencv2/geometry.hpp>   // OpenCV 5.x: getAffineTransform 在这
#include <opencv2/imgproc.hpp>    // warpAffine 还在这
cv::Mat* OpencvCal::currImage()
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);
    std::string path = "rec/image/chess.bmp";
    m_currImage = cv::imread(path, cv::IMREAD_COLOR);
    return &m_currImage;
}
bool OpencvCal::gammaLut(const int maxValue, const double gamma,std::vector<uint16_t>& lut)
{
    lut.resize(maxValue+1);
    // 生成 Gamma 查找表
    for (int i = 0; i <= maxValue; ++i)
    {
        const double normalized =
            static_cast<double>(i) / maxValue;

        const double corrected =
            maxValue * std::pow(normalized, 1.0 / gamma);

        lut[i] = static_cast<uint16_t>(
            std::round(corrected));
    }
    return true;
}

bool OpencvCal::Gamma_Cal(const cv::Mat& src,
                          const double gamma,
                          cv::Mat& out)
{
    out.release();

    if (src.empty() || gamma <= 0.0 ||
        !std::isfinite(gamma))
    {
        return false;
    }

    const int depth = src.depth();
    const int channels = src.channels();

    // 8-bit 和 16-bit 整数图像使用 LUT
    if (depth == CV_8U || depth == CV_16U)
    {
        const int maxValue =
            depth == CV_8U ? 255 : 65535;

        std::vector<uint16_t> lut(maxValue + 1);

        gammaLut(gamma,maxValue,lut);

        out.create(src.size(), src.type());

        const size_t total =
            src.total() * channels;

        if (depth == CV_8U)
        {
            const uchar* input = src.ptr<uchar>();
            uchar* output = out.ptr<uchar>();

            for (size_t i = 0; i < total; ++i)
                output[i] = static_cast<uchar>(lut[input[i]]);
        }
        else
        {
            const uint16_t* input = src.ptr<uint16_t>();
            uint16_t* output = out.ptr<uint16_t>();

            for (size_t i = 0; i < total; ++i)
                output[i] = lut[input[i]];
        }

        return true;
    }

    // 32-bit 和 64-bit 浮点图像
    if (depth == CV_32F || depth == CV_64F)
    {
        src.convertTo(out, src.type());

        const size_t total = src.total() * channels;

        if (depth == CV_32F)
        {
            const float* input = src.ptr<float>();
            float* output = out.ptr<float>();

            for (size_t i = 0; i < total; ++i)
            {
                const double v = input[i];

                if (!std::isfinite(v))
                    return false;

                output[i] = static_cast<float>(
                    std::pow(std::max(0.0, std::min(1.0, v)),
                             1.0 / gamma));
            }
        }
        else
        {
            const double* input = src.ptr<double>();
            double* output = out.ptr<double>();

            for (size_t i = 0; i < total; ++i)
            {
                const double v = input[i];

                if (!std::isfinite(v))
                    return false;

                output[i] = std::pow(
                    std::max(0.0, std::min(1.0, v)),
                    1.0 / gamma);
            }
        }

        return true;
    }

    return false;
}
OpencvCal::OpencvCal()
{
    cv::utils::logging::setLogLevel(
        cv::utils::logging::LOG_LEVEL_WARNING
    );
   // std::string path = "rec/image/chess.bmp";
  // m_currImage = cv::imread(path, cv::IMREAD_COLOR);
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
