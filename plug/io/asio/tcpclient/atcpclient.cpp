//
// Created by 25137 on 25-10-1.

#include "atcpclient.h"
#include <QDebug>

ATCPClient::ATCPClient(IO::Config con,QObject* parent)
    :QObject(parent)
    ,IOInterface("atcpclient",con)
    ,_socket(new tcp::socket(io_context))
{
    auto fun = [this](const IO::Frame& frame)
    {
        emit rx_frame(frame);
    };
    addCallback(0,fun);
}

ATCPClient::~ATCPClient()
{
    try {
        // 先停止接受新工作
        io_context.stop();

        // 等待所有操作完成（如果有工作线程）
        if (io_thread_.joinable()) {
            io_thread_.join();
        }

        // 清理剩余工作（可选）
        io_context.restart();
        while (io_context.poll()) {
            // 执行剩余handlers
        }
    }
    catch (...) {
        // 记录日志，但不抛出异常
     //   qWarning() << "Exception in ATCPClient destructor";
    }
}

void ATCPClient::run() {
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


bool ATCPClient::open() {
    std::error_code ec;

    // 服务器地址和端口
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(config.dev.toStdString(), ec),
                                     config.ch.toInt());

    if (ec) {
        qWarning() << "Invalid IP address:" << QString::fromStdString(ec.message());
        return false;
    }

    // 尝试连接
    _socket->connect(endpoint, ec);
    if (ec) {
        qWarning() << "Failed to connect:" << QString::fromLocal8Bit(ec.message().c_str());
        return false;
    }

    qDebug() << QString("Connected to server:%1:%2 <==> client:%3:%4")
    .arg(QString::fromStdString(endpoint.address().to_string()))
    .arg(endpoint.port())
    .arg(QString::fromStdString(_socket->local_endpoint().address().to_string()))
    .arg(_socket->local_endpoint().port())
    ;
    run();
    return true;
}
bool ATCPClient::close() {

    return true;
}
int ATCPClient::write(const IO::Frame& frame) {
    if (_socket->is_open())
    {
        _socket->async_write_some(
            asio::buffer(frame.data.data(),frame.data.size())
            ,[this, frame](std::error_code ec, std::size_t length) {
          if (ec) {
             qDebug() << "发送失败: " <<QString::fromStdString(ec.message()) ;
          }
          else
          {
              
          }
      }
            );

    }
    return 0;
}
int ATCPClient::write(const QList<IO::Frame>&) {
    return 0;
}

