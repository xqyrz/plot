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
bool OpencvCal::getHistogram(const cv::Mat& src, cv::Mat& hist, int channel, int bins, bool normalize,
                             const cv::Mat& mask)
{
    hist.release();

    if (src.empty() || bins <= 0)
        return false;

    if (channel < 0 || channel >= src.channels())
        return false;

    // 确定直方图范围
    float range[] = { 0.0f, 256.0f };

    switch (src.depth())
    {
    case CV_8U:
        range[0] = 0.0f;
        range[1] = 256.0f;
        break;

    case CV_16U:
        range[0] = 0.0f;
        range[1] = 65536.0f;
        break;

    case CV_32F:
    case CV_64F:
        range[0] = 0.0f;
        range[1] = 1.0f;
        break;

    default:
        return false;
    }

    // 检查 Mask
    if (!mask.empty())
    {
        if (mask.type() != CV_8UC1 ||
            mask.size() != src.size())
            return false;
    }

    int channels[] = { channel };
    int histSize[] = { bins };

    const float* ranges[] = { range };
    //int channels[] = {0}; // 统计 B 通道
    // channels[] = {1}; // 统计 G 通道
    // channels[] = {2}; // 统计 R 通道
    // 计算直方图
    cv::calcHist(
        &src, //图片
        1,//图片数量
        channels,//通道索引
        mask,//用来只统计 ROI 区域
        hist,//out:输出直方图
        1,//直方图维度（1 = 灰度一维，2=HSV 的 H-S 二维直方图）
        histSize,//每一维 bin 数量数组
        ranges//每一维数值范围的数组的数组
    );

    // 归一化
    if (normalize)
    {
        double total = cv::sum(hist)[0];

        if (total > 0.0)
            hist /= total;
    }

    return true;
}
bool OpencvCal::getHistogram(const cv::Mat& src, cv::Mat& hist, int channel, int bins, bool normalize,
                             const cv::Mat& mask, bool multiColor)
{
    hist.release();
    if (src.empty() || bins <= 0)
        return false;

    // ========== 三维颜色直方图：统计BGR组合颜色出现次数 ==========
    if (multiColor)
    {
        // 只支持 8UC3 BGR图
        if (src.channels() != 3 || src.depth() != CV_8U)
            return false;

        // mask校验
        if (!mask.empty())
        {
            if (mask.type() != CV_8UC1 || mask.size() != src.size())
                return false;
        }

        int channels[] = {0, 1, 2};   // B, G, R
        int histSize[] = {bins, bins, bins};
        float range[] = {0.0f, 256.0f};
        const float* ranges[] = {range, range, range};

        cv::calcHist(
            &src,
            1,
            channels,
            mask,
            hist,
            3,          // 三维直方图
            histSize,
            ranges
        );

        // 归一化：次数 / 总像素，变成占比
        if (normalize)
        {
            double total = cv::sum(hist)[0];
            if (total > 1e-9)
            {
                hist /= total;
            }
        }
        return true;
    }

    // ========== 原有逻辑：单通道一维直方图 ==========
    if (channel < 0 || channel >= src.channels())
        return false;

    float range[] = {0.0f, 256.0f};
    switch (src.depth())
    {
    case CV_8U:
        range[0] = 0.0f;
        range[1] = 256.0f;
        break;
    case CV_16U:
        range[0] = 0.0f;
        range[1] = 65536.0f;
        break;
    case CV_32F:
    case CV_64F:
        range[0] = 0.0f;
        range[1] = 1.0f;
        break;
    default:
        return false;
    }

    if (!mask.empty())
    {
        if (mask.type() != CV_8UC1 || mask.size() != src.size())
            return false;
    }

    int channels[] = {channel};
    int histSize[] = {bins};
    const float* ranges[] = {range};

    cv::calcHist(&src, 1, channels, mask, hist, 1, histSize, ranges);

    if (normalize)
    {
        double total = cv::sum(hist)[0];
        if (total > 1e-9)
        {
            hist /= total;
        }
    }
    return true;
}
bool OpencvCal::toLuminance(const cv::Mat& src, cv::Mat& gray)
{
    gray.release();
    if (src.empty())
        return false;

    const int depth = src.depth();
    const int ch = src.channels();

    // 已经是单通道，直接当亮度用（灰度图 / 16 位 L 图）
    if (ch == 1)
    {
        gray = src;
        return true;
    }

    if (depth != CV_8U && depth != CV_16U && depth != CV_32F)
        return false;
    if (ch != 3 && ch != 4)
        return false;

    try
    {
        //penCV 颜色空间转换函数
        //
        //@NOTE: 转灰度图
        cv::cvtColor(src, gray, ch == 4 ? cv::COLOR_BGRA2GRAY : cv::COLOR_BGR2GRAY);
    }
    catch (const cv::Exception& e)
    {
        std::cerr << "toLuminance failed: " << e.what() << std::endl;
        gray.release();
        return false;
    }

    return !gray.empty();
}

bool OpencvCal::getLuminanceHistogram(const cv::Mat& src, cv::Mat& hist, int bins,
                                      bool normalize, const cv::Mat& mask)
{
    hist.release();
    if (src.empty() || bins <= 0)
        return false;

    cv::Mat gray;
    if (!toLuminance(src, gray))
        return false;

    // 浮点图统一按 [0,1] 统计；若实际是 0~255 的浮点图，自动缩放
    if (gray.depth() == CV_32F)
    {
        double mn = 0.0, mx = 0.0;
        cv::minMaxLoc(gray, &mn, &mx);
        if (mn < 0.0 || mx > 1.0)
        {
            if (mn >= -1e-6 && mx <= 255.0 + 1e-6)
            {
                std::cerr << "getLuminanceHistogram: float image not in [0,1], scale by 1/255" << std::endl;
                gray = gray / 255.0f;
            }
            else
            {
                return false;   // 范围未知，统计出来没意义
            }
        }
    }

    // 复用一维单通道直方图逻辑
    return getHistogram(gray, hist, 0, bins, normalize, mask);
}

VisionCal::ImageLuminance OpencvCal::getLuminance(const cv::Mat& src)
{
    VisionCal::ImageLuminance result{};
    if (src.empty())
        return result;

    const int depth = src.depth();
    const int ch = src.channels();

    CV_Assert(depth == CV_8U || depth == CV_16U || depth == CV_32F || depth == CV_64F);
    CV_Assert(ch == 1 || ch == 3 || ch == 4);

    double scale = 1.0;
    switch (depth)
    {
    case CV_8U:
        scale = 1.0 / 255.0;
        break;
    case CV_16U:
        scale = 1.0 / 65535.0;
        break;
    case CV_32F:
    case CV_64F:
        scale = 1.0;
        break;
    default:
        return result;
    }

    cv::Mat f32;
    // 统一转到 CV_32F，不再用昂贵的 CV_64F
    src.convertTo(f32, CV_32F, static_cast<float>(scale));

    cv::Mat rgbFloat;
    if (ch == 1)
    {
        // 灰度：luma = 灰度本身
        rgbFloat = f32;
    }
    else if (ch == 4)
    {
        cv::cvtColor(f32, rgbFloat, cv::COLOR_BGRA2BGR);
    }
    else
    {
        rgbFloat = f32;
    }

    double y601Norm = 0.0;
    double y709Norm = 0.0;

    if (rgbFloat.channels() == 1)
    {
        // 灰度图：y601 == y709
        cv::Scalar m = cv::mean(rgbFloat);
        y601Norm = m[0];
        y709Norm = m[0];
    }
    else
    {
        // BGR -> luma，用 transform，单趟 SIMD
        static const cv::Mat_<float> k601 = (cv::Mat_<float>(1, 3) << 0.114f, 0.587f, 0.299f);
        static const cv::Mat_<float> k709 = (cv::Mat_<float>(1, 3) << 0.0722f, 0.7152f, 0.2126f);

        cv::Mat y601Mat, y709Mat;
        cv::transform(rgbFloat, y601Mat, k601);
        cv::transform(rgbFloat, y709Mat, k709);

        y601Norm = cv::mean(y601Mat)[0];
        y709Norm = cv::mean(y709Mat)[0];
    }

    // [0,1] → [0,100]，修复原来覆盖 bug
    result.y601 = y601Norm * 100.0;
    result.y709 = y709Norm * 100.0;

    // 如果要 L*，正确版本附在下面，不要直接拿浮点 BGR 进 cvtColor
    // result.lStar = calcMeanLStar(src);

    return result;
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
bool OpencvCal::gammaLut(const cv::Mat& src, const double gamma, std::vector<uint16_t>& table)
{
    return gammaLut(maxValue(src),gamma,table);
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
int OpencvCal::maxValue(const cv::Mat& src)
{
    if (src.empty() )
    {
        return 0;
    }

    const int depth = src.depth();
    const int channels = src.channels();

    // 8-bit 和 16-bit 整数图像使用 LUT
   // if (depth == CV_8U || depth == CV_16U)
    {
        return depth == CV_8U ? 255 : 65535;
    }
}
bool OpencvCal::Lut_Cal(const cv::Mat& src, const std::vector<uint16_t>& lut, cv::Mat& out)
{
   if ((maxValue(src)+1) != lut.size())return false;
    const int depth = src.depth();
    const int channels = src.channels();

    // 8-bit 和 16-bit 整数图像使用 LUT
    //if (depth == CV_8U || depth == CV_16U)
    {

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
    return true;
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
