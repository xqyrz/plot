//
// Created by hw on 2025/10/2.
//

#ifndef PLOT_SELFIOAPP_H
#define PLOT_SELFIOAPP_H

#include "ioappinterface.h"
#include "mavlink/selfio/mavlink.h"

class SelfIOAPP:public QObject,public IOAPPInterface{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOAPPInterface_Id FILE "selfioapp.json")
    Q_INTERFACES(IOAPPInterface)
public:
    explicit SelfIOAPP( QObject* parent = nullptr);
    QList<IOAPP::SIGNALS>  decode(const IO::Frame& data) override ;
    IO::Frame encode() override;
signals:
   void hasSignal(const QList<IOAPP::SIGNALS>&);
private slots:
    void rx_frame(const IO::Frame&);
private:
    mavlink_message_t rcv_msg;
    mavlink_status_t status;
    const uint8_t sys_id = 1;
    const uint8_t comp_id = 1;
};


#endif //PLOT_SELFIOAPP_H