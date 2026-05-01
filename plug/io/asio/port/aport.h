//
// Created by 25137 on 26-2-7.
//

#ifndef APORT_H
#define APORT_H
#if _MSC_VER >= 1900
#pragma execution_character_set("utf-8")
#endif
#include "iointerface.h"
#include "asio.hpp"

class  APort:public IOInterface_obj,public IOInterface
{
    Q_OBJECT
    Q_INTERFACES(IOInterface)
    Q_PLUGIN_METADATA(IID IOInterface_Id FILE "port.json")

public:
    explicit APort( QObject* parent = nullptr,IO::Config config=IO::Config());
    ~APort() override;
    void run() override;
    bool open() override;
    bool close() override;
    int write(const IO::Frame&) override;
    int write(const QList<IO::Frame>&) override;
    QList<std::tuple<QVariant::Type,QString,QVariant>> getConfig() override;
    void setConfig(const QList<std::tuple<QVariant::Type,QString,QVariant>> &) override;
    signals:
            void rx_frame(const IO::Frame&);
public   slots:
    void tx_frame(const IO::Frame& frame){write(frame);};
private:
    void do_read();
private:
    asio::io_context io_context;
    std::unique_ptr<asio::serial_port> handle;
    std::thread io_thread_;
    std::array<char, 1024> recv_buffer_;
    const QStringList stop{"1","1.5","2"};
    const QStringList check{ "NONE","ODD", "EVEN","MARK","SPACE"};\
    const QStringList flow{"NONE"};
};


#endif //APORT_H
