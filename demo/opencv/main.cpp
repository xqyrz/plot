//
// Created by 25137 on 2026/10/25.
//
#include "opencvcal.h"
#include <iostream>

int main()
{
    // 字符串版本
    std::cout << "CV_VERSION: " << CV_VERSION << "\n";
    OpencvCal cal;

    // 6. 显示与保存
    cv::imshow("currImage", *cal.currImage());

    cv::Mat out;
    auto size = cal.currImage()->size();

    auto M = cal.move(64,0,size);
    cal.Affine_Transformation(M, out);
    cv::imshow("currImage->moveX 64", out);
    cal.Affine_Transformation(cal.move(0,64,size,M), out);
    cv::imshow("currImage->moveX 64->moveY 64", out);

     M = cal.rotate(10,size);
    cal.Affine_Transformation(M, out);
    cv::imshow("currImage->rotate 10", out);

     M = cal.scale(0.5,2,size);
    cal.Affine_Transformation(M, out);
    cv::imshow("currImage->scale 0.9,0.8", out);

    cv::waitKey(0);
    return 0;
}
