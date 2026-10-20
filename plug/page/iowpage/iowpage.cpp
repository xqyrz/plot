//
// Created by 25137 on 26-3-13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_IOWPage.h" resolved

#include "iowpage.h"
#include <QDebug>
#include <QFile>
#include <QScrollBar>
#include <QTextStream>
#include "../../../common/plug/io/iointerface.h"
#include "ui_iowpage.h"
IOWPage::IOWPage(QWidget *parent) :
    PageBase(parent), m_ui(new Ui::IOWPage) {

    QFile file(":/iowpage/rec/defalut.qss");
    m_inputPorts << PLUG::InputType::IN_IO_TX;
    m_outputPorts << PLUG::OutputType::OUT_IO_RX;
    // 以只读方式打开文件（资源文件/本地文件都支持）
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
    }
    QTextStream stream(&file);
    ui()->setStyleSheet(stream.readAll());

    m_ui->setupUi(ui());
    m_ui->splitter->setHandleWidth(4);
    m_ui->splitter_2->setHandleWidth(4);
    m_ui->clearR->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_ui->clearT->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    // 【关键设置】关闭自动换行
    m_ui->textBrowser->setLineWrapMode(QTextBrowser::NoWrap);

    // 可选：显示水平滚动条（不换行后内容超长会需要横向滚动）
    m_ui->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    m_funs.insert(keyStr(IOOBJS),[this](const void*  data)
    {
        auto _d =static_cast<const QList<IOInterface*>*>(data);
        if (_d)setIOobjs(*_d);
    });
}

IOWPage::~IOWPage() {
    delete m_ui;
}

void IOWPage::on_devOpen_clicked()
{
    if (fun)
    {
        QJsonObject obj;
        obj[KEY] = CONFIG_KEY;
        QJsonObject data;
        data["port"] = m_ui->port->currentText();
        // data["baud"]=
    }
    else
    {
        qWarning() << "not set callback";
    }
}
void IOWPage::slots_IN_IO_TX(const PLUG::Frame& frame)
{
    m_ui->tableIO->addRow(frame);
    //TODO:timer 定时 优化性能
    m_ui->textBrowser->insertPlainText(frame.data);
    if (m_ui->tableIO->updateFlag())
    {
        QScrollBar *scrollBar = m_ui->textBrowser->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    }
}

void IOWPage::setIOobjs(const QList<IOInterface*>& _objs){
    ioObjs = _objs;
    m_ui->ioobj->clear();
    for (auto & var:ioObjs)
    {
        m_ui->ioobj->addItem(var->getName(),reinterpret_cast<qlonglong>(var));
    }
}

