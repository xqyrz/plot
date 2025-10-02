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
    int decode(QByteArray& data) override ;
    int encode(QByteArray& data) override;
private:
    mavlink_message_t rcv_msg;
    mavlink_status_t status;
};


#endif //PLOT_SELFIOAPP_H