//
// Created by 25137 on 26-3-13.
//

#ifndef IOWPAGE_H
#define IOWPAGE_H

#include <QWidget>
#include <functional>
#include <QJsonObject>
#include "../pagebase.h"
#include "../io/iocommon.h"
QT_BEGIN_NAMESPACE
namespace Ui { class IOWPage; }
QT_END_NAMESPACE

class IOWPage : public QWidget,public PageBase {
Q_OBJECT
    Q_INTERFACES(PageBase)
    Q_PLUGIN_METADATA(IID PageBase_Id FILE "iowpage.json")
public:
    explicit IOWPage(QWidget *parent = nullptr);
    ~IOWPage() override;

private slots:
    void on_devOpen_clicked();
public slots:
    void  slot_rx(const IO::Frame&);
public:
    const char* getSignal(int index) const override ;
    const char* getSlot(int index) const override ;
private:
    Ui::IOWPage *ui;
    std::function<void(QJsonObject&)> fun;
};


#endif //IOWPAGE_H
