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
    void setImagePath(QString const &path)
    {
        m_imagePath = path;
    }
    QString getImagePath() const
    {
        return m_imagePath;
    }
    QList<std::pair<QString, QImage>> images()
    {
        QList<std::pair<QString, QImage>> images;
        if(m_imagePath.isEmpty())
            return images;
        if(!QFile::exists(m_imagePath))
            return images;
        m_image.load(m_imagePath);
        images.append(std::make_pair(m_imagePath, m_image));
        return images;
    }
private:
    QImage m_image;
    QString m_imagePath;
};


#endif // PLOT_IMAGENODEDATA_H
