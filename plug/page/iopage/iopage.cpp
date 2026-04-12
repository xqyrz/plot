//
// Created by 25137 on 26-2-10.
//

#include "iopage.h"
#include <QQuickView>
#include <QVBoxLayout>
#include <QQuickItem>
IOPage::IOPage(QWidget* parent)
    :QWidget(parent),
    PageBase()
{
    qDebug()<<"hello world";
    QQuickView *view = new QQuickView();
  view->setSource(QUrl("qrc:/iopage.qml"));
   auto root = view->rootObject();
  if (root) {
      // 设置属性，例如全局字体大小
      root->setProperty("font.pointSize", 16);
  }
    auto container = QWidget::createWindowContainer(view, this);
    qDebug()<< container;
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(container);
}
