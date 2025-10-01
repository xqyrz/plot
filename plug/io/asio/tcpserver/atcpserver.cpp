//
// Created by 25137 on 25-10-1.

#include "atcpserver.h"
#include <QDebug>

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(tcp::socket socket) : socket_(std::move(socket)) {}
    void start() { do_read(); }

private:
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length]{};

    void do_read() {
        auto self(shared_from_this());
        socket_.async_read_some(
            asio::buffer(data_, max_length),
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    qDebug() << "Received: " << QByteArray(data_, length).toHex(' '); // NOLINT(*-narrowing-conversions)
                    do_write(length);
                }
            }
        );
    }
    void do_write(std::size_t length) {
        auto self(shared_from_this());
        asio::async_write(
            socket_,
            asio::buffer(data_, length),
            [this](std::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    do_read();
                }
            }
        );
    }
};

ATCPServer::ATCPServer(IO::Config con,QObject* parent)
    :QObject(parent),IOInterface("atcpserver",con)
    ,acceptor_(new tcp::acceptor(io_context))
{
}

ATCPServer::~ATCPServer() = default;

void ATCPServer::run() {
    std::thread io_thread([&]() {
        try {
            io_context.run();
        } catch (std::exception& e) {
            qWarning() << "Exception: " << e.what();
        }
    });

}


bool ATCPServer::open() {
    std::error_code ec;
    //acceptor_->set_option(tcp::acceptor::reuse_address(true));
    acceptor_->open(tcp::v4(), ec);
    if (ec) {
        qWarning() << "Failed to open acceptor: " << QString::fromStdString(ec.message()) ;
        return false;
    }
    acceptor_->bind(
    asio::ip::tcp::endpoint (asio::ip::tcp::v4(), config.ch.toInt()), ec);
    if (ec) {
         qWarning() <<"Failed to bind: " << QString::fromStdString(ec.message()) ;
        return false;
    }
    try {
        auto local_ep = acceptor_->local_endpoint();
        acceptor_->listen(asio::socket_base::max_listen_connections);
        qInfo() << "Listening on port "
                <<local_ep.port()<<":"
                <<QString::fromStdString(local_ep.address().to_string());
        acceptor_->async_accept(
    [this](std::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<Session>(std::move(socket))->start();
                }
                do_accept();
            });
    }
    catch (const std::system_error& e) {
        qWarning() << "Listen failed: " << e.what();
    }
    catch (const std::exception& e) { // 捕获其他 std::exception
        qWarning() << "Unexpected exception: " << e.what();
    }


    return false;
}
bool ATCPServer::close() {

    return true;
}
QList<IO::Frame> ATCPServer::readALL() {

    return std::exchange(rBuffer, {});
}
int ATCPServer::write(const QList<IO::Frame>&) {
    return 0;
}

void ATCPServer::do_accept() {
    acceptor_->async_accept(
    [this](std::error_code ec, tcp::socket socket) {
        if (!ec) {
            auto  remote_ep = socket.remote_endpoint();
            qInfo()<<"Accept connection from "
            <<QString::fromStdString(remote_ep.address().to_string())
            << ":" << remote_ep.port();
            sessions.push_back(std::make_unique<Session>(std::move(socket)));
            sessions.back()->start();
        }
        do_accept();
    }
);
}
