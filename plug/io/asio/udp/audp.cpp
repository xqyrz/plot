//
// Created by 25137 on 25-10-5.
//

#include "audp.h"
#include <QDebug>
AUdp::AUdp(IO::Config config, QObject *parent)    :QObject(parent)
    ,IOInterface("aUdp",config)
    ,_socket(new udp::socket(io_context))
    ,recv_buffer_()
{

}

AUdp::~AUdp() {
}

void AUdp::run() {

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

bool AUdp::open() {

try {
    std::error_code ec;
    _socket.reset(new udp::socket(io_context,udp::endpoint(
    config.own_dev.size()?udp::v6():udp::v4()
    , config.own_ch.toInt())));

    do_read();
    // 服务器地址和端口
    // endpoint=asio::ip::udp::endpoint(
    //     asio::ip::make_address(config.dev.toStdString(), ec),
    //        config.ch.toInt());
    //
    // if (ec) {
    //     qWarning() << "Invalid IP address:" << QString::fromStdString(ec.message());
    //     return false;
    // }

    // 尝试连接
    //_socket->connect(endpoint, ec);
    if (ec) {
        qWarning() << "Failed to connect:" << QString::fromStdString(ec.message());
        return false;
    }

    qDebug() << QString("Connected to local: %1:%2")// <==> remote: %3:%4")
    .arg(QString::fromStdString(_socket->local_endpoint().address().to_string()))
    .arg(_socket->local_endpoint().port())
    // .arg(QString::fromStdString(endpoint.address().to_string()))
    // .arg(endpoint.port())
    ;
    run();
}catch (const std::exception& e) {
    qWarning() << "Exception in io_thread thread:" << QString::fromLocal8Bit(e.what());
}catch (...) {
    qWarning() << "Unknown exception in io_context thread";
}
    return true;
}

bool AUdp::close() {
    return false;
}

int AUdp::write(const IO::Frame & frame) {
    if (!_socket->is_open()) {return 0;}
    return _socket->send(asio::buffer(frame.data.data(), frame.data.size()));
}

int AUdp::write(const QList<IO::Frame> & frames) {

    foreach (const IO::Frame & frame, frames) {
        write(frame);
    }
    return 0;
}

void AUdp::do_read() {
    _socket->async_receive_from(
        asio::buffer(recv_buffer_), endpoint,
        [this](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
               //  qDebug()<<QString("%1:%2 %3")
               // .arg(QString::fromLocal8Bit(endpoint.address().to_string().c_str()))
               // .arg(endpoint.port())
               // .arg(QString( QByteArray(recv_buffer_.data(), bytes_recvd).toHex(' ')));

                QList<IO::Frame> frames;
                auto  remote_ep = endpoint;
                frames.append(IO::Frame{
                    {
                        QString::fromStdString(remote_ep.address().to_string()),
                        QString::number(remote_ep.port())
                    },
                    QDateTime::currentDateTime(),
                    QByteArray(recv_buffer_.data(),bytes_recvd)
                });
                this->_readReady(frames);
            } else {
                // 出错或接收长度为 0
                if (ec)
                    qWarning() << "Receive error: " <<QString::fromLocal8Bit(ec.message().c_str());
            }
            // 继续监听下一个包
            do_read();
        });

}


