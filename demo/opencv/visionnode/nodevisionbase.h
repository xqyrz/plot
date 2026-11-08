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
class ImageLabel;
class VisionConfigPage;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class NodeVisionBase: public NodeDelegateModel
{
    Q_OBJECT
public:
    NodeVisionBase();
     ~NodeVisionBase();
    QList<std::pair<QString,QImage>> images();

    unsigned int nPorts(PortType portType) const override;
    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
    std::shared_ptr<NodeData> outData(PortIndex port) override;

    QString caption() const override { return QString::fromLatin1(metaObject()->className()); }
    bool captionVisible() const override { return true; }
    QString name() const override { return QString::fromLatin1(metaObject()->className()); }


    QWidget *embeddedWidget() override;

    void setInData(std::shared_ptr<NodeData>, PortIndex) override {};
private slots:
    virtual void _updateConfig(){};
    virtual void _configInt(){};
    virtual void _configOpen(){};
private:
    void _setImage(QImage&);

public :
    void setImage(QImage& image){_setImage(image);};
     void showConfigPage();

protected:
    QList<NodeDataType> m_inPorts;
    QList<NodeDataType> m_outPorts;
    std::shared_ptr<ImageNodeData> m_imageData;
    ImageLabel *m_imageItem{nullptr};
    VisionConfigPage* configPage();
private:
   // QImage m_image;
    VisionConfigPage* m_configPage{nullptr};

};


#endif // PLOT_VISIONBASENODE_H
