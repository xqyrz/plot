//
// Created by 25137 on 2026/10/27.
//
#pragma once

#include "../nodevisionbase.h"

class ImageLabel;

class NodeImage : public NodeVisionBase
{
    Q_OBJECT

public:
    NodeImage();

    virtual ~NodeImage() {}

public:
    QString caption() const override { return QStringLiteral("image"); }

    bool captionVisible() const override { return false; }

    QString name() const override { return QStringLiteral("Image"); }

public:
    void showConfigPage() override;


    QJsonObject save() const override;

    void load(QJsonObject const &p) override;

public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex) override {}

    QWidget *embeddedWidget() override;
    QList<std::pair<QString,QImage>> images();
public:


private Q_SLOTS:

    void onTextEdited(QString const &string);
private:
    std::shared_ptr<ImageNodeData> m_imageData;

    ImageLabel *m_imageItem{nullptr};
};
