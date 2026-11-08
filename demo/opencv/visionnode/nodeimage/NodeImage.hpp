//
// Created by 25137 on 2026/10/27.
//
#pragma once

#include "../nodevisionbase.h"

class ImageLabel;
class SelectImage;
class NodeImage : public NodeVisionBase
{
    Q_OBJECT

public:
    NodeImage();

    virtual ~NodeImage() {}


public:

    QJsonObject save() const override;

    void load(QJsonObject const &p) override;


private:

private slots:
    void _updateConfig() override;
    void _configInt() override;
    void _configOpen() override;
private Q_SLOTS:
    void onTextEdited(QString const &string);

private:
    SelectImage* selectImage{nullptr};
};
