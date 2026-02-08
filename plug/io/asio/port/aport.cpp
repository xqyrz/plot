//
// Created by 25137 on 26-2-7.
//

#include "aport.h"
#include <QDebug>
#include <QThread>
#include <chrono>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
using namespace  asio;
APort::APort(QObject* parent, IO::Config config)
    :QObject(parent),
    IOInterface("aport",config),
    handle(new serial_port(io_context))
{

    this->config.dev = "COM4";
    this->config.ch = R"({
        "baud":1152000,
        "data":8,
        "stop":0,
        "parity":0,
        "flow":0
    })";
    addCallback(0,[this](const IO::Frame& frame)
    {
        emit rx_frame(frame);
    });
}
APort::~APort()
{

}
void APort::run()
{
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
bool APort::open()
{
    try {
        handle->open(config.dev.toStdString());
        QJsonObject obj = QJsonDocument::fromJson(config.ch.toUtf8()).object();
        if (!obj.isEmpty())
        {
            auto baud = obj.value("baud").toInt();
            auto data = obj.value("data").toInt();
            auto stop = obj.value("stop").toInt();
            auto parity = obj.value("parity").toInt();
            auto flow = obj.value("flow").toInt();
            handle->set_option(serial_port::baud_rate(baud?baud:9600));
            handle->set_option(serial_port::character_size(data?data:8));
            switch (stop)
            {
                case 0:handle->set_option(serial_port::stop_bits(serial_port::stop_bits::one));break;
                case 1:handle->set_option(serial_port::stop_bits(serial_port::stop_bits::onepointfive));break;
                case 2:handle->set_option(serial_port::stop_bits(serial_port::stop_bits::two));break;
                default:throw std::runtime_error("not stop bit");break;
            }

            handle->set_option(serial_port::parity(static_cast<serial_port::parity::type>(parity)));
            handle->set_option(serial_port::flow_control(static_cast<serial_port::flow_control::type>(flow)));
            qInfo()<<"open "<<config.dev<<" baud "<<baud<<" data "<<data<<" stop "<<stop<<" parity "<<parity<<" flow "<<flow;
            do_read();
            run();
        }
    }
    catch (const std::exception& e) {
       qWarning() << "open port fail: " << QString::fromUtf8(e.what());
        std::cout<<e.what()<<std::endl;
    }
    return true;
}
bool APort::close()
{
    handle->close();
    return true;
}
int APort::write(const IO::Frame& frame)
{
    if (!handle->is_open()) {return 0;}
    return handle->write_some(asio::buffer(frame.data.data(), frame.data.size()));
}
int APort::write(const QList<IO::Frame>& frames)
{
    foreach (const IO::Frame& frame, frames)
    {
        write(frame);
    }
    return 0;
}
void APort::do_read()
{
    handle->async_read_some(
    asio::buffer(recv_buffer_),
    [this](std::error_code ec, std::size_t bytes_recvd) {
        if (!ec && bytes_recvd > 0) {
            QList<IO::Frame> frames;
            frames.append(IO::Frame{
                this->config,
                QDateTime::currentDateTime(),
                QByteArray(recv_buffer_.data(),bytes_recvd)
            });
           //  qDebug()<<QString("%1:%2 %3 (%4)")
           // .arg(config.dev)
           // .arg(" ")
           // .arg(QString( frames.last().data.toHex(' ')))
           //  .arg(QString(frames.last().data));
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
