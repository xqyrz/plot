//
// Created by 25137 on 26-3-13.
//

#ifndef IOWPAGE_H
#define IOWPAGE_H

#include <QJsonObject>
#include <QWidget>
#include <functional>
#include <QQueue>
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
private:
      void timerEvent(QTimerEvent *event) override;
private slots:
    void on_devOpen_clicked();
public slots:
   void slots_IN_IO_RX(const PLUG::Frame&) override;
    void setIOobjs(const QList<IOInterface*>&);
public:

private:
    Ui::IOWPage *m_ui;
    std::function<void(QJsonObject&)> fun;
    QList<IOInterface*> ioObjs;
    QQueue<PLUG::Frame> m_rFrames;
    int m_rTimer{0};
};


#endif //IOWPAGE_H
