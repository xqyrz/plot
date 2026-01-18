//
// Created by 25137 on 25-10-1.
//

#ifndef ATCPSERVER_H
#define ATCPSERVER_H

#include "iointerface.h"
#include "asio.hpp"
using asio::ip::tcp;
class ATCPClient:public QObject,public IOInterface{
    Q_OBJECT
    //    Q_PLUGIN_METADATA(IID IOInterface_Id)
    Q_PLUGIN_METADATA(IID IOInterface_Id FILE "atcpclient.json")
    Q_INTERFACES(IOInterface)
public:
    explicit ATCPClient(IO::Config config=IO::Config(), QObject* parent = nullptr);
    ~ATCPClient() override;
    void run() override;
    bool open() override;
    bool close() override;
    int write(const IO::Frame&) override;
    int write(const QList<IO::Frame>&) override;
    signals:
        void rx_frame(const IO::Frame&);
public   slots:
    void tx_frame(const IO::Frame& frame){write(frame);};
private:

private:
    asio::io_context io_context;
    std::unique_ptr<tcp::socket> _socket;
    std::thread io_thread_;
};



#endif //ATCPSERVER_H
