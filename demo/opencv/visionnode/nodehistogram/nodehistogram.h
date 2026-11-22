//
// Created by 25137 on 2026/11/15.
//

#ifndef PLOT_NODEHISTOGRAM_H
#define PLOT_NODEHISTOGRAM_H


#include "../nodevisionbase.h"
class HistogramItem;
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
    void color_cnt();
    void rgb_cnt();
private:
    HistogramItem* m_item{nullptr};
    int binNum = 64;
};



#endif // PLOT_NODEHISTOGRAM_H
