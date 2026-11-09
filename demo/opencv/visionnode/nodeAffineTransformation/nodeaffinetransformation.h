//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_NODEAFFINETRANSFORMATION_H
#define PLOT_NODEAFFINETRANSFORMATION_H

#include "../nodevisionbase.h"
#include <array>
class AffineTransformationItem;
class nodeAffineTransformation:public NodeVisionBase
{
    Q_OBJECT
public:
    nodeAffineTransformation();
    ~nodeAffineTransformation() override;
    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex) override;
    void setM( std::array<double, 9> _M);
private slots:
    void _configInt() override;
    void _configOpen() override;
    void _updateConfig() override;
private:
   AffineTransformationItem* m_item;
    std::array<double, 9> M;
};


#endif // PLOT_NODEAFFINETRANSFORMATION_H
