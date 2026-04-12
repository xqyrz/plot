//
// Created by 25137 on 26-3-13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_IOWPage.h" resolved

#include "iowpage.h"
#include "ui_iowpage.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <bus/MessageBus>
#include <bus/bus>
IOWPage::IOWPage(QWidget *parent) :
    QWidget(parent), ui(new Ui::IOWPage) {

    QFile file(":/iowpage/rec/defalut.qss");
    // 以只读方式打开文件（资源文件/本地文件都支持）
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
    }
    QTextStream stream(&file);
    setStyleSheet(stream.readAll());

    ui->setupUi(this);
    ui->splitter->setHandleWidth(4);
    ui->splitter_2->setHandleWidth(4);
    ui->clearR->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->clearT->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    bus_subscribe<bus::IoConfig>("robot/*", this, [](const bus::IoConfig& p){
    qDebug() << p.ch().baud();
    });
}

IOWPage::~IOWPage() {
    delete ui;
}

void IOWPage::on_devOpen_clicked()
{
    if(fun){
        QJsonObject obj;
        obj[KEY]=CONFIG_KEY;
        QJsonObject data;
        data["port"]=ui->port->currentText();
        //data["baud"]=
    }
    else{
        qWarning()<<"not set callback";
    }
}

