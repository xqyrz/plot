//
// Created by 25137 on 26-3-13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_IOWPage.h" resolved

#include "iowpage.h"
#include "ui_iowpage.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QScrollBar>
#include "iointerface.h"
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
    // 【关键设置】关闭自动换行
    ui->textBrowser->setLineWrapMode(QTextBrowser::NoWrap);

    // 可选：显示水平滚动条（不换行后内容超长会需要横向滚动）
    ui->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    m_funs.insert(keyStr(IOOBJS),[this](const void*  data)
    {
        auto _d =static_cast<const QList<IOInterface*>*>(data);
        if (_d)setIOobjs(*_d);
    });
}

IOWPage::~IOWPage() {
    delete ui;
}

void IOWPage::on_devOpen_clicked()
{
    if (fun)
    {
        QJsonObject obj;
        obj[KEY] = CONFIG_KEY;
        QJsonObject data;
        data["port"] = ui->port->currentText();
        // data["baud"]=
    }
    else
    {
        qWarning() << "not set callback";
    }
}
void IOWPage::slot_rx(const IO::Frame& frame)
{
    ui->tableIO->addRow(frame);
    //TODO:timer 定时 优化性能
    ui->textBrowser->insertPlainText(frame.data);
    if (ui->tableIO->updateFlag())
    {
        QScrollBar *scrollBar = ui->textBrowser->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    }
}
const char* IOWPage::getSignal(int index) const {


return nullptr;
}

const char* IOWPage::getSlot(int index) const {
    switch (index)
    {
    case 0:return SLOT(slot_rx(const IO::Frame&));break;
    default:return nullptr;
    }
}

void IOWPage::setIOobjs(const QList<IOInterface*>& _objs){
    ioObjs = _objs;
    ui->ioobj->clear();
    for (auto & var:ioObjs)
    {
        ui->ioobj->addItem(var->getName(),reinterpret_cast<qlonglong>(var));
    }
}

