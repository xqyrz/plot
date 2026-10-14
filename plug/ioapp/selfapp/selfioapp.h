//
// Created by hw on 2025/10/2.
//

#ifndef PLOT_SELFIOAPP_H
#define PLOT_SELFIOAPP_H

#include "ioapp/ioappinterface.h"
#include "mavlink/selfio/mavlink.h"

class SelfIOAPP:public IOAPPInterface{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IOAPPInterface_Id FILE "selfioapp.json")
    Q_INTERFACES(IOAPPInterface)
public:
    explicit SelfIOAPP( QObject* parent = nullptr);
    QList<INC::_SIGNALS>  decode(const INC::Frame& data) override ;
    INC::Frame encode() override;
signals:
   void hasSignal(const QList<INC::_SIGNALS>&);
    void sig_app_rx(const INC::Frame&);
private slots:
    void rx_frame(const INC::Frame&);
private:
    mavlink_message_t rcv_msg;
    mavlink_status_t status;
    const uint8_t sys_id = 1;
    const uint8_t comp_id = 1;
    qint64 __time = 0;
};


#endif //PLOT_SELFIOAPP_H