//
// Created by hw on 2025/10/2.
//

#ifndef PLOT_SELFIOAPP_H
#define PLOT_SELFIOAPP_H

#include "ioappinterface.h"

class VOFAAPP:public QObject,public IOAPPInterface{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOAPPInterface_Id FILE "selfioapp.json")
    Q_INTERFACES(IOAPPInterface)
public:
    explicit VOFAAPP( QObject* parent = nullptr);
    QList<IOAPP::SIGNALS>  decode(const IO::Frame& data) override ;
    IO::Frame encode() override;
     QList<std::tuple<QVariant::Type,QString,QVariant>> showConfigDialog() override;
     void setConfigDialog(const QList<std::tuple<QVariant::Type,QString,QVariant>> &)override;
signals:
   void hasSignal(const QList<IOAPP::SIGNALS>&);
private slots:
    void rx_frame(const IO::Frame&);
private:
    const uint8_t sys_id = 1;
    const uint8_t comp_id = 1;
    qint64 __time = 0;
    QByteArray buffer;
    QTime _last;
    QList<QString> sigNames;
};


#endif //PLOT_SELFIOAPP_H