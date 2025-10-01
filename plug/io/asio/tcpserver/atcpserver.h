//
// Created by 25137 on 25-10-1.
//

#ifndef ATCPSERVER_H
#define ATCPSERVER_H

#include "iointerface.h"
#include "asio.hpp"
class Session;

using asio::ip::tcp;
class ATCPServer:public QObject,public IOInterface{
    Q_OBJECT
    //    Q_PLUGIN_METADATA(IID IOInterface_Id)
    Q_PLUGIN_METADATA(IID IOInterface_Id FILE "atcpserver.json")
    Q_INTERFACES(IOInterface)
public:
    explicit ATCPServer(IO::Config config=IO::Config(), QObject* parent = nullptr);
    ~ATCPServer();
    void run() override;
    bool open() override;
    bool close() override;
    QList<IO::Frame> readALL() override;
    int write(const QList<IO::Frame>&) override;
private:
    void do_accept();
private:
    asio::io_context io_context;
    std::unique_ptr<tcp::acceptor> acceptor_;
    std::list< std::unique_ptr<Session>> sessions;
};



#endif //ATCPSERVER_H
