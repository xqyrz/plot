//
// Created by 25137 on 25-10-1.
//

#ifndef ATCPSERVER_H
#define ATCPSERVER_H

#include "../../../../common/plug/io/iointerface.h"
#include "asio.hpp"
class Session;

using asio::ip::tcp;
class  ATCPServer:public IOInterface{
    Q_OBJECT
    Q_INTERFACES(IOInterface)
    Q_PLUGIN_METADATA(IID IOInterface_Id FILE "atcpserver.json")

public:
    explicit ATCPServer(PLUG::Config config=PLUG::Config(), QObject* parent = nullptr);
    ~ATCPServer();
    void run() override;
    bool open() override;
    bool close() override;
    int write(const PLUG::Frame&)override;
    int write(const QList<PLUG::Frame>&) override;
    auto & getSessions(){return sessions;}
    auto & getAccept(){return acceptor_;}
    signals:
    void rx_frame(const PLUG::Frame&);
public   slots:
    void tx_frame(const PLUG::Frame& frame){write(frame);};
private:
    void do_accept();
private:
    asio::io_context io_context;
    std::unique_ptr<tcp::acceptor> acceptor_;
    std::list< std::shared_ptr<Session>> sessions;
    std::thread io_thread_;
};



#endif //ATCPSERVER_H
