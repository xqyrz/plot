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
        m_images.clear();
        if(m_imagePath.isEmpty())return;
        if(!QFile::exists(m_imagePath))return;
        QImage m_image;
        m_image.load(m_imagePath);
        m_images.append(std::make_pair(m_imagePath, m_image));
    }
    void clear(){m_images.clear();}
    void setImage(const QString& name,QImage& image)
    {
        for (auto&var:m_images)
        {
            if (var.first == name)
            {
                var.second = image;
                return;
            }
        }
        m_images.append(std::make_pair(name, image));
    }
    QString getImagePath() const
    {
        return m_imagePath;
    }
    const QList<std::pair<QString, QImage>>& images()
    {
        return m_images;
    }
private:
    QList<std::pair<QString, QImage>>  m_images;
    QString m_imagePath;
};



#endif // PLOT_IMAGENODEDATA_H
