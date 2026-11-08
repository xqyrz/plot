//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_VISIONBASENODE_H
#define PLOT_VISIONBASENODE_H

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>

#include <iostream>
#include "imagenodedata.h"
class DecimalData;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class NodeVisionBase: public NodeDelegateModel
{
    Q_OBJECT
public:
QList<QImage> images();
private:
    void _setImage(QImage&);
public :
    void setImage(QImage& image){_setImage(image);};
    virtual void showConfigPage(){};
private:
    QImage m_image;
};


#endif // PLOT_VISIONBASENODE_H
