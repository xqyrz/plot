//
// Created by 25137 on 2026/10/27.
//

#ifndef PLOT_VISIONCALPAGE_H
#define PLOT_VISIONCALPAGE_H

#include <QtNodes/GraphicsView>

 namespace QtNodes
{
    class VisionFlowGraphicsScene;
    class VisionFlowGraphModel;
};
using namespace QtNodes;
class VisionCalPage : public GraphicsView
{
    Q_OBJECT
public:
    VisionCalPage(QWidget *parent = Q_NULLPTR);
private:

signals:
    void updateImage(QList<std::pair<QString, QImage>>);
private:
    VisionFlowGraphModel* m_model{nullptr};
    VisionFlowGraphicsScene* m_scene{nullptr};


};


#endif // PLOT_VISIONCALPAGE_H
