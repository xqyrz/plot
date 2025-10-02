//
// Created by 25137 on 25-10-1.

#include "atcpserver.h"
#include <QDebug>

class Session : public std::enable_shared_from_this<Session> {
public:
    using Ptr = std::shared_ptr<Session>;
    using CloseCallback = std::function<void(Ptr)>;
    using ReadCallback = std::function<void(const Ptr&, const char*,size_t)>;
    explicit Session(tcp::socket socket)
        : socket_(std::move(socket)) {}

    void start() { do_read(); }

    void set_close_callback(CloseCallback cb) { on_close_ = std::move(cb); }
    void set_read_callback(ReadCallback cb) { on_read_ = std::move(cb); }
    auto getRemoteEndpoint() { return this->socket_.remote_endpoint(); }
private:
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length]{};
    CloseCallback on_close_;
    ReadCallback on_read_;
    void do_read() {
       auto self = shared_from_this();
        socket_.async_read_some(
            asio::buffer(data_, max_length),
            [self](std::error_code ec, std::size_t length) {
                if (!ec) {
                    if (self->data_[length-1] == 0)
                    {
                       // qDebug() << "r:" << QByteArray(self->data_, length).toHex(' ');
                     //   qDebug() << "Received:"<<self->data_;
                    }
                    else
                    {
//                        qDebug() << "r:" << QByteArray(self->data_, length).toHex(' ');
                    }
                  //  self->do_write(length);
                    if (self->on_read_)
                    {
                        self->on_read_(self,self->data_,length);
                    }
                    self->do_read();
                }
                else
                {
                    if (ec == asio::error::eof){
                        auto remote_ep = self->socket_.remote_endpoint();
                        qInfo() << QString("Client disconnected %1:%2")
                      .arg(QString::fromStdString(remote_ep.address().to_string()))
                      .arg(remote_ep.port());
                }
                    else
                        qWarning() << QString("Read error:%1").arg(ec.message().data());
                    // 通知服务器移除 session
                    if (self->on_close_) self->on_close_(self);
                }
            }
        );
    }

    void do_write(std::size_t length) {
        auto self = shared_from_this();
        asio::async_write(
            socket_,
            asio::buffer(data_, length),
            [self](std::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    self->do_read();
                } else {
                    if (ec == asio::error::eof)
                        qInfo() << "Client disconnected";
                    else
                        qWarning() << QString("Write error::%1").arg(ec.message().data());
                    if (self->on_close_) self->on_close_(self);
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

ATCPServer::~ATCPServer()
{
    qDebug()<<"~ATCPServer";
    io_context.stop();
    io_thread_.join();
}

void ATCPServer::run() {
    io_thread_ = std::thread([this]() {
        try {
            io_context.run();  // 阻塞直到所有工作完成或 stop() 被调用
        } catch (const std::exception& e) {
            qWarning() << "Exception in io_context thread:" << e.what();
        } catch (...) {
            qWarning() << "Unknown exception in io_context thread";
        }
    });

}


bool ATCPServer::open() {
    std::error_code ec;

    // 打开 acceptor
    acceptor_->open(tcp::v4(), ec);
    if (ec) {
        qWarning() << "Failed to open acceptor:" << QString::fromStdString(ec.message());
        return false;
    }

    // 设置选项
    acceptor_->set_option(tcp::acceptor::reuse_address(true), ec);
    if (ec) {
        qWarning() << "Failed to set reuse_address:" << QString::fromStdString(ec.message());
    }

    // 绑定端口
    auto endpoint = tcp::endpoint(tcp::v4(), config.ch.toInt());
    acceptor_->bind(endpoint, ec);
    if (ec) {
        qWarning() << "Failed to bind:" << QString::fromStdString(ec.message());
        return false;
    }

    // 监听
    acceptor_->listen(asio::socket_base::max_listen_connections, ec);
    if (ec) {
        qWarning() << "Listen failed:" << QString::fromStdString(ec.message());
        return false;
    }

    // 输出本地地址
    try {
        auto local_ep = acceptor_->local_endpoint();
        qInfo() << QString("Listening: %1:%2")
                      .arg(QString::fromStdString(local_ep.address().to_string()))
                      .arg(local_ep.port());
    } catch (const std::exception& e) {
        qWarning() << "Failed to get local endpoint:" << e.what();
    }

    // 开始接受连接
    do_accept();
    run();
    return true;
}
bool ATCPServer::close() {

    return true;
}
int ATCPServer::write(const IO::Frame&)
{
    return 0;
}
int ATCPServer::write(const QList<IO::Frame>&) {
    return 0;
}

void ATCPServer::do_accept() {
    acceptor_->async_accept([self = this](std::error_code ec, tcp::socket socket) {
            if (!ec) {
                try {
                    auto remote_ep = socket.remote_endpoint();
                    qInfo() << QString("Accepted connection from %1:%2")
                      .arg(QString::fromStdString(remote_ep.address().to_string()))
                      .arg(remote_ep.port());

                    auto session = std::make_shared<Session>(std::move(socket));
                    session->set_close_callback([self](Session::Ptr s) {
                                auto& vec = self->getSessions();
                                vec.erase(std::remove(vec.begin(), vec.end(), s), vec.end());
                               // qInfo() << "Session removed, remaining:" << vec.size();
                            });
                    session->set_read_callback([self](Session::Ptr s, const char* data, size_t length)
                    {
                        QList<IO::Frame> frames;
                        auto  remote_ep = s->getRemoteEndpoint();
                        frames.append(IO::Frame{
                            {
                                QString::fromStdString(remote_ep.address().to_string()),
                                QString::number(remote_ep.port())
                            },
                            QDateTime::currentDateTime(),
                            QByteArray(data,length)
                        });
                        self->_readReady(frames);
                    });
                    self->getSessions().push_back(std::move(session));
                     self->getSessions().back()->start();
                } catch (const std::exception& e) {
                    qWarning() << "Failed to handle new connection:" << e.what();
                }
            } else {
                // 可以打印日志，但不要总是报错，EC可能是io_context停止或acceptor关闭
                if (ec != asio::error::operation_aborted)
                    qWarning() << "Accept error:" << QString::fromStdString(ec.message());
            }

            // 只有 acceptor 仍然打开时才继续
            if (self->getAccept() && self->getAccept()->is_open()) {
                self->do_accept();
            }
        }
    );
}
