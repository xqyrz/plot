//
// Created by 25137 on 25-10-5.
//

#ifndef AUDP_H
#define AUDP_H

#include "iointerface.h"
#include "asio.hpp"
using asio::ip::udp;

class  AUdp:public IOInterface_obj,public IOInterface{
    Q_OBJECT
    Q_INTERFACES(IOInterface)
    Q_PLUGIN_METADATA(IID IOInterface_Id FILE "audp.json")

public:
    explicit AUdp( QObject* parent = nullptr,IO::Config config=IO::Config());
    ~AUdp() override;
    void run() override;
    bool open() override;
    bool close() override;
    int write(const IO::Frame&) override;
    int write(const QList<IO::Frame>&) override;
     QList<std::tuple<QVariant::Type,QString,QVariant>> showConfigDialog() override;

signals:
    void rx_frame(const IO::Frame&);
public   slots:
    void tx_frame(const IO::Frame& frame){write(frame);};
private:
    void do_read();
private:
    asio::io_context io_context;
    std::unique_ptr<udp::socket> _socket;
    std::thread io_thread_;
    udp::endpoint endpoint;
    std::array<char, 1024> recv_buffer_;
};
// QT_BEGIN_NAMESPACE
// #define UDP_Id "IO.Plugin.udp"
// Q_DECLARE_INTERFACE(AUdp, UDP_Id);
// QT_END_NAMESPACE

#endif //AUDP_H
