#pragma once

#include "iointerface.h"
#include <array>
#include "jlinkarm.h"
class AJLinkArm :public QObject, public IOInterface
{
    Q_OBJECT
        Q_PLUGIN_METADATA(IID IOInterface_Id FILE "ajlinkarm.json")
        Q_INTERFACES(IOInterface)
public:
    explicit AJLinkArm(IO::Config config = IO::Config(), QObject* parent = nullptr);
    ~AJLinkArm() override;
    void run() override;
    bool open() override;
    bool close() override;
    int write(const IO::Frame&) override;
    int write(const QList<IO::Frame>&) override;
signals:
        void rx_frame(const IO::Frame&);
public   slots:
    void tx_frame(const IO::Frame& frame){write(frame);};
private:
    void do_read();
private:
    std::array<char, 1024> recv_buffer_;
};
