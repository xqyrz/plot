|项目	|cv::warpAffine	|cv::warpPerspective
变换类型	仿射变换 Affine	透视变换（单应变换 Homography）
矩阵大小	2×3，float (CV_32F)	3×3，double 居多 (CV_64F)
自由度	6 个自由度	8 个自由度（3x3 矩阵最后一个元素固定为 1）
控制点数量	最少 3 对 点 getAffineTransform	最少 4 对 点 getPerspectiveTransform
几何约束	✅ 直线保持直线
✅ 平行线依旧平行	✅ 直线保持直线
❌ 平行线可以汇聚到灭点（近大远小）
能做什么	平移、旋转、缩放、错切 (斜切)	包含仿射全部能力 + 透视投影、四点矫正、鸟瞰转换
不能做	近大远小透视效果，四边形任意拉伸矫正	无（仿射是它特例）
坐标公式	[x′y′​]=M2×3​​xy1​​	​x′y′w′​​=H3×3​​xy1​​
归一化：u=x′/w′,v=y′/w′
计算速度	更快，计算简单	稍慢，多了除法归一化
典型场景	图像旋转、平移、缩放、简单对齐	文档矫正、车牌矫正、俯视图转换、图像拼接、SLAM 单应匹配
边界模式	全部 BorderTypes 都支持	全部 BorderTypes 都支持，但REFLECT/WRAP 非常不推荐
常用插值	INTER_LINEAR / INTER_NEAREST	INTER_LINEAR / INTER_NEAREST