//
// Created by 25137 on 2026/10/31.
//

#ifndef PLOT_IMAGENODEDATA_H
#define PLOT_IMAGENODEDATA_H

#include <QtNodes/NodeDelegateModel>
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;
class ImageNodeData:public NodeData
{
public:
    ImageNodeData() {}
    NodeDataType type() const override
    {
        return {"id","iamge"};
    }
    void setImagePath(const QString &path)
    {
        m_imagePath = path;
    }
    QString getImagePath() const
    {
        return m_imagePath;
    }
private:
    QVector<uint8_t> m_imageu8;
    QString m_imagePath;
};


#endif // PLOT_IMAGENODEDATA_H
