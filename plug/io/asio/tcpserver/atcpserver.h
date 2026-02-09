//
// Created by 25137 on 25-10-1.
//

#ifndef ATCPSERVER_H
#define ATCPSERVER_H

#include "iointerface.h"
#include "asio.hpp"
class Session;

using asio::ip::tcp;
class  ATCPServer:public QObject,public IOInterface{
    Q_OBJECT
    Q_INTERFACES(IOInterface)
    Q_PLUGIN_METADATA(IID IOInterface_Id FILE "atcpserver.json")

public:
    explicit ATCPServer(IO::Config config=IO::Config(), QObject* parent = nullptr);
    ~ATCPServer();
    void run() override;
    bool open() override;
    bool close() override;
    int write(const IO::Frame&)override;
    int write(const QList<IO::Frame>&) override;
    auto & getSessions(){return sessions;}
    auto & getAccept(){return acceptor_;}
    signals:
    void rx_frame(const IO::Frame&);
public   slots:
    void tx_frame(const IO::Frame& frame){write(frame);};
private:
    void do_accept();
private:
    asio::io_context io_context;
    std::unique_ptr<tcp::acceptor> acceptor_;
    std::list< std::shared_ptr<Session>> sessions;
    std::thread io_thread_;
};



#endif //ATCPSERVER_H
