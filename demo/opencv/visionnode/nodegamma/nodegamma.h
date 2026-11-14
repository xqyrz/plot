//
// Created by 25137 on 2026/11/14.
//

#ifndef PLOT_NODEGAMMA_H
#define PLOT_NODEGAMMA_H

#include "../nodevisionbase.h"
class GammaItem;
class NodeGamma:public NodeVisionBase
{
    Q_OBJECT
public:
    NodeGamma(){};
    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex) override;
private slots:
    void _configInt() override;
    void _configOpen() override;
    void _updateConfig() override;
private:
    GammaItem* m_item{nullptr};
    std::vector<uint16_t> _lut;
};


#endif // PLOT_NODEGAMMA_H
