//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_NODEAFFINETRANSFORMATION_H
#define PLOT_NODEAFFINETRANSFORMATION_H

#include "../nodevisionbase.h"

class AffineTransformationItem;
class nodeAffineTransformation:public NodeVisionBase
{
    Q_OBJECT
public:
    nodeAffineTransformation();
    ~nodeAffineTransformation() override;
    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex) override;

private slots:
    void _configInt() override;
    void _configOpen() override;
    void _updateConfig() override;
private:
   AffineTransformationItem* m_item;

};


#endif // PLOT_NODEAFFINETRANSFORMATION_H
