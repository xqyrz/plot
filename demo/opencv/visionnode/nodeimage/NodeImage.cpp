//
// Created by 25137 on 2026/10/27.
//
#include "NodeImage.hpp"

// "DecimalData.hpp"

#include <QFileInfo>
#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include <QtWidgets/QMenu>

#include "../imageLabel.h"
#include "../visionconfigpage.h"
#include  "selectimage.h"
NodeImage::NodeImage()
{
    setProperty("tilt","读取图片");
    setProperty("desc","选择一张图片读取");
    setProperty("help","选择完成后点击确定");
    m_inPorts.clear();
    embeddedWidget();
    connect(m_imageItem, &QWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QMenu menu(m_imageItem);                 // parent 设为控件，保证点击空白处能自动关闭
        menu.addAction("选择图片", [this]
        {
            m_imageItem->slecetImagePath(m_imageData->getImagePath());
        });
        menu.exec(m_imageItem->mapToGlobal(pos)); // 局部坐标 → 屏幕坐标
    });
    connect(m_imageItem,&ImageLabel::textChanged,[this](QString const & _t1)
    {
        m_imageData->setImagePath(_t1);
        Q_EMIT configClicked(this);
    });
}


QJsonObject NodeImage::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["path"] = m_imageData->getImagePath();

    return modelJson;
}

void NodeImage::load(QJsonObject const &p)
{
    QJsonValue v = p["path"];

    if (!v.isUndefined()) {
        QString strNum = v.toString();
            if (m_imageItem)
                m_imageItem->setImagePath(v.toString());
        m_imageData->setImagePath(v.toString());
    }
}
void NodeImage::_updateConfig()
{
     m_imageItem->setImagePath( selectImage->filePath());
}
void NodeImage::_configInt()
{
    selectImage = new SelectImage();

    connect(selectImage, &SelectImage::imageChanged, this, [this](const QString &path)
    {
            QList<std::pair<QString, QImage>> list;
        list.append(std::pair<QString, QImage>{});
        QFileInfo fi(path);
        if (!fi.isFile())
        {
            qWarning() << "[ImageLoad] 不是有效文件:" << path;
            return;
        }
            list.last().first = fi.fileName();
        if (!list.last().second.load(path))
        {
            qWarning() << "[ImageLoad] QImage::load 失败:" << path;
            return;
        }

        if (auto *page = configPage())
        {
            page->showImage(list);
        }
    });

    configPage()->setConfigPropertyItem(selectImage);
}
void NodeImage::_configOpen()
{
    selectImage->setFilePath(m_imageData->getImagePath());
}


void NodeImage::onTextEdited(QString const &str)
{
    bool ok = false;

    double number = str.toDouble(&ok);

    if (ok) {
       // _number = number;

        Q_EMIT dataUpdated(0);

    } else {
        Q_EMIT dataInvalidated(0);
    }
}


