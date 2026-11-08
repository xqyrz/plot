//
// Created by 25137 on 2026/10/27.
//
#include "NodeImage.hpp"

// "DecimalData.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include <QtWidgets/QMenu>

#include "iamgelabel.h"

NodeImage::NodeImage()
    : m_imageItem{nullptr}
    , m_imageData(new ImageNodeData())
{}

void NodeImage::showConfigPage()
{
  qobject_cast<ImageLabel*>(embeddedWidget())->slecetImagePath(m_imageData->getImagePath());
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

unsigned int NodeImage::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = 0;
        break;

    case PortType::Out:
        result = 1;

    default:
        break;
    }

    return result;
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


NodeDataType NodeImage::dataType(PortType, PortIndex) const
{
    return {"1","2"};
}

std::shared_ptr<NodeData> NodeImage::outData(PortIndex)
{
    return m_imageData;
}

QWidget *NodeImage::embeddedWidget()
{
    if (!m_imageItem) {
        m_imageItem = new ImageLabel();
        m_imageItem->setMinimumWidth(50);
        m_imageItem->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(m_imageItem, &QWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
            QMenu menu(m_imageItem);                 // parent 设为控件，保证点击空白处能自动关闭
            menu.addAction("选择图片", [this]
            {
                m_imageItem->slecetImagePath(m_imageData->getImagePath());
            });
       //     menu.addAction("选择图片路径", [this]{ m_imageItem->copy(); });
            menu.exec(m_imageItem->mapToGlobal(pos)); // 局部坐标 → 屏幕坐标
        });
        connect(m_imageItem,&ImageLabel::textChanged,[this](QString const & _t1)
        {
            m_imageData->setImagePath(_t1);
            Q_EMIT configClicked(this);
       //} else {
       //    Q_EMIT dataInvalidated(0);
       //}
        });
    }
    return m_imageItem;
}
QList<std::pair<QString, QImage>> NodeImage::images()
{
    return m_imageData->images();
}


