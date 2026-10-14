//
// Created by 25137 on 25-10-1.
//

#ifndef ATCPSERVER_H
#define ATCPSERVER_H

#include "../../../../common/plug/io/iointerface.h"
#include "asio.hpp"
using asio::ip::tcp;
class ATCPClient:public IOInterface{
    Q_OBJECT
    Q_INTERFACES(IOInterface)
    //    Q_PLUGIN_METADATA(IID IOInterface_Id)
    Q_PLUGIN_METADATA(IID IOInterface_Id FILE "atcpclient.json")

public:
    explicit ATCPClient(PLUG::Config config=PLUG::Config(), QObject* parent = nullptr);
    ~ATCPClient() override;
    void run() override;
    bool open() override;
    bool close() override;
    int write(const PLUG::Frame&) override;
    int write(const QList<PLUG::Frame>&) override;
    signals:
        void rx_frame(const PLUG::Frame&);
public   slots:
    void tx_frame(const PLUG::Frame& frame){write(frame);};
private:

private:
    asio::io_context io_context;
    std::unique_ptr<tcp::socket> _socket;
    std::thread io_thread_;
};



#endif //ATCPSERVER_H
