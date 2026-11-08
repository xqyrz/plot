//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_VISIONFLOWGRAPHICSSCENE_H
#define PLOT_VISIONFLOWGRAPHICSSCENE_H

#include <QtNodes/DataFlowGraphicsScene>
#include <qobjectdefs.h>


namespace QtNodes
{
    class VisionFlowGraphModel;
    class VisionFlowGraphicsScene:public DataFlowGraphicsScene
    {
        Q_OBJECT
    public:
        VisionFlowGraphicsScene(VisionFlowGraphModel &graphModel, QObject *parent = nullptr);
    private:
        void _init();
    };
}
#endif // PLOT_VISIONFLOWGRAPHICSSCENE_H
