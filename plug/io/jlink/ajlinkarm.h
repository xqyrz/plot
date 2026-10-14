#pragma once

#include <array>
#include "../../../common/plug/io/iointerface.h"
#include "jlinkarm.h"
class JlinkARM;
class QTimer;
class AJLinkArm : public IOInterface
{
    Q_OBJECT
        Q_PLUGIN_METADATA(IID IOInterface_Id FILE "ajlinkarm.json")
        Q_INTERFACES(IOInterface)
public:
    explicit AJLinkArm(PLUG::Config config = PLUG::Config(), QObject* parent = nullptr);
    ~AJLinkArm() override;
    void run() override;
    bool open() override;
    bool close() override;
    int write(const PLUG::Frame&) override;
    int write(const QList<PLUG::Frame>&) override;
signals:
        void rx_frame(const PLUG::Frame&);
public   slots:
    void tx_frame(const PLUG::Frame& frame){write(frame);};
private:
    void do_read();
private:
    std::array<char, 1024> recv_buffer_;
    JlinkARM* _handle;
    QTimer* timer;
};
