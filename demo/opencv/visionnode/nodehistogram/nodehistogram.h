//
// Created by 25137 on 2026/11/15.
//

#ifndef PLOT_NODEHISTOGRAM_H
#define PLOT_NODEHISTOGRAM_H


#include "../nodevisionbase.h"
class PlotView;
class NodeHistogram:public NodeVisionBase
{
    Q_OBJECT
public:
    NodeHistogram();
    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex const portIndex) override;
private slots:
    void _configInt() override;
    void _configOpen() override;
    void _updateConfig() override;
private:
    PlotView* m_item{nullptr};
};



#endif // PLOT_NODEHISTOGRAM_H
