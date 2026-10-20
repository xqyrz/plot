//
// Created by 25137 on 26-3-13.
//

#ifndef IOWPAGE_H
#define IOWPAGE_H

#include <QJsonObject>
#include <QWidget>
#include <functional>
#include "page/pagebase.h"
QT_BEGIN_NAMESPACE
namespace Ui { class IOWPage; }
QT_END_NAMESPACE
class IOInterface;
class IOWPage : public PageBase {
Q_OBJECT
    Q_INTERFACES(PageBase)
    Q_PLUGIN_METADATA(IID PageBase_Id FILE "iowpage.json")
public:
    explicit IOWPage(QWidget *parent = nullptr);
    ~IOWPage() override;

private slots:
    void on_devOpen_clicked();
public slots:
   void slots_IN_IO_TX(const PLUG::Frame&) override;
    void setIOobjs(const QList<IOInterface*>&);
public:

private:
    Ui::IOWPage *m_ui;
    std::function<void(QJsonObject&)> fun;
    QList<IOInterface*> ioObjs;
};


#endif //IOWPAGE_H
