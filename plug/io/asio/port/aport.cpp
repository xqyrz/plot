//
// Created by 25137 on 26-2-7.
//
#if _MSC_VER >= 1900
#pragma execution_character_set("utf-8")
#endif
#include "aport.h"
#include <QDebug>
#include <QThread>
#include <chrono>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <QtSerialPort/QSerialPortInfo>
#include <utility>
using namespace  asio;
APort::APort(QObject* parent, IO::Config config)
    :QObject(parent),
    IOInterface("aport",std::move(config)),
    handle(new serial_port(io_context))
{

    this->config.dev = "COM4";
    this->config.ch = R"({
        "baud":1152000,
        "data":8,
        "stop":"1",
        "parity":"NONE",
        "flow":"NONE"
    })";
    addCallback(0,[this](const IO::Frame& frame)
    {
        emit rx_frame(frame);
    });
}
APort::~APort()
{

}

// Windows 平台下获取串口
std::vector<std::string> list_available_ports_windows() {
    std::vector<std::string> comPorts;
    HKEY hKey;
    LONG result;

    // 打开设备管理器中的COM端口注册表项
    result = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        "HARDWARE\\DEVICEMAP\\SERIALCOMM",
        0, KEY_READ, &hKey);

    if (result == ERROR_SUCCESS) {
        char valueName[256];
        char portName[256];
        DWORD valueNameSize, portNameSize, type;
        DWORD index = 0;

        while (true) {
            valueNameSize = sizeof(valueName);
            portNameSize = sizeof(portName);

            result = RegEnumValue(hKey, index, valueName,
                &valueNameSize, NULL, &type,
                (LPBYTE)portName, &portNameSize);

            if (result == ERROR_NO_MORE_ITEMS) {
                break;
            }

            if (result == ERROR_SUCCESS && type == REG_SZ) {
                comPorts.push_back(portName);
            }

            index++;
        }

        RegCloseKey(hKey);
    }

    return comPorts;
}

// Linux 平台下获取串口
std::vector<std::string> list_available_ports_linux() {
    std::vector<std::string> ports;
#ifdef _WIN32
#else

    // 打开 /dev 目录
    DIR* dir = opendir("/dev");
    if (dir == nullptr) {
        std::cerr << "Failed to open /dev directory!" << std::endl;
        return ports;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename(entry->d_name);

        // 串口设备通常以 tty 或 ttyUSB 开头
        if (filename.find("tty") == 0 || filename.find("ttyUSB") == 0) {
            std::string port_name = "/dev/" + filename;
            ports.push_back(port_name);
        }
    }

    closedir(dir);
#endif
    return ports;
}

// 跨平台扫描串口
QStringList list_available_ports() {
    QStringList ports;

#ifdef _WIN32
    // Windows 平台扫描串口
   auto com = list_available_ports_windows();
#else
    // Linux/Unix 平台扫描串口
    auto com = list_available_ports_linux();
#endif
    for (auto&var:com)
    {
        ports.append(QString::fromStdString(var));
    }
    return ports;
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
QList<std::tuple<QVariant::Type, QString, QVariant>> APort::showConfigDialog()
{
    QList<std::tuple<QVariant::Type, QString, QVariant>> temp;
    // auto ports = QSerialPortInfo::availablePorts();
    auto ports = list_available_ports();
    auto obj = QJsonDocument::fromJson(config.ch.toUtf8()).object();
    if (ports.contains(config.dev))
    {
        ports.removeOne(config.dev);
        ports.insert(0,config.dev);
    }
    temp.append(std::make_tuple(QVariant::StringList, "COM", ports));
    temp.append(std::make_tuple(QVariant::Int, "波特率", obj["baud"].toInt()));
    temp.append(std::make_tuple(QVariant::Int, "数据位", obj["data"].toInt()));
    auto _stop = stop;
    if (_stop.contains(obj["stop"].toString()))
    {
        auto var = obj["stop"].toString();
        _stop.removeOne(var);
        _stop.insert(0,var);
    }
    temp.append(std::make_tuple(QVariant::StringList, "停止位", _stop));
    auto _check = check;
    if (_check.contains(obj["parity"].toString()))
    {
        auto var = obj["parity"].toString();
        _check.removeOne(var);
        _check.insert(0,var);
    }
    auto _flow = flow;
    if (_flow.contains(obj["flow"].toString()))
    {
        auto var = obj["flow"].toString();
        _flow.removeOne(var);
        _flow.insert(0,var);
    }
    temp.append(std::make_tuple(QVariant::StringList, "校验位", _check));
    temp.append(std::make_tuple(QVariant::StringList, "流控位", _flow));
    return temp;
}
void APort::setConfigDialog(const QList<std::tuple<QVariant::Type, QString, QVariant>>& tuples)
{
    auto obj = QJsonDocument::fromJson(config.ch.toUtf8()).object();
    for (auto& t:tuples)
    {
        qDebug()<<std::get<0>(t)<<std::get<1>(t)<<std::get<2>(t);
        if (std::get<1>(t) == "COM")
        {
            config.dev = std::get<2>(t).toString();
        }
        else  if (std::get<1>(t) == "波特率")
        {
            obj["baud"] =  std::get<2>(t).toInt();
        }
        else if (std::get<1>(t) == "数据位")
        {
            obj["data"] =  std::get<2>(t).toInt();
        }
        else if (std::get<1>(t) == "停止位")
        {
            obj["stop"] =  std::get<2>(t).toString();
        }
        else if (std::get<1>(t) == "校验位")
        {
            obj["parity"] =  std::get<2>(t).toString();
        }
        else if (std::get<1>(t) == "流控位")
        {
            obj["flow"] =  std::get<2>(t).toString();
        }
    }
    config.ch = QJsonDocument(obj).toJson();
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
