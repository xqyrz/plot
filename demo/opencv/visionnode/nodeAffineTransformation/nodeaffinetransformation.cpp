//
// Created by 25137 on 2026/11/8.
//

#include "nodeaffinetransformation.h"
nodeAffineTransformation::nodeAffineTransformation()
{
    setProperty("tilt","2D变换");
    setProperty("desc","投影，仿射，(放缩:scale(double),旋转rotate(double),移动move(x(double),y,z)");
    setProperty("help","可以配置变换矩阵参数");
}
void nodeAffineTransformation::setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex)
{
    auto data =static_cast<ImageNodeData*>(nodeData.get());
    qDebug()<<"- "<<data->images();
}
