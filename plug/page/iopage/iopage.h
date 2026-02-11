//
// Created by 25137 on 26-2-10.
//

#ifndef IOPAGE_H
#define IOPAGE_H
#include <QQuickView>
#include <QWidget>

#include "../pagebase.h"
class QQuickView;
class IOPage : public QWidget, public PageBase
{
    Q_OBJECT
public:
    IOPage(QWidget* parent = nullptr);
private:
    QQuickView *view;
};



#endif //IOPAGE_H
