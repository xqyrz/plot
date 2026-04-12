//
// Created by 25137 on 26-3-13.
//

#ifndef IOWPAGE_H
#define IOWPAGE_H

#include <QWidget>
#include <functional>
#include <QJsonObject>
#include "page/pagebase.h"
QT_BEGIN_NAMESPACE
namespace Ui { class IOWPage; }
QT_END_NAMESPACE

class IOWPage : public QWidget,public PageBase {
Q_OBJECT

public:
    explicit IOWPage(QWidget *parent = nullptr);
    ~IOWPage() override;

private slots:
    void on_devOpen_clicked();

private:
    Ui::IOWPage *ui;
    std::function<void(QJsonObject&)> fun;
};


#endif //IOWPAGE_H
