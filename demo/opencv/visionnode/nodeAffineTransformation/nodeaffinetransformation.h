//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_NODEAFFINETRANSFORMATION_H
#define PLOT_NODEAFFINETRANSFORMATION_H

#include "../nodevisionbase.h"
class nodeAffineTransformation:public NodeVisionBase
{
    Q_OBJECT
public:
    nodeAffineTransformation();
    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex) override;
};


#endif // PLOT_NODEAFFINETRANSFORMATION_H
