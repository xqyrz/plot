#include "ajlinkarm.h"


AJLinkArm::AJLinkArm(IO::Config config, QObject* parent)
    :QObject(parent)
    ,IOInterface("aJlinkArm", config)
{
    addCallback(0,[this](const IO::Frame& frame)
{
    emit rx_frame(frame);
});
}

AJLinkArm::~AJLinkArm()
{
}

void AJLinkArm::run()
{
}

bool AJLinkArm::open()
{
    return false;
}

bool AJLinkArm::close()
{
    return false;
}

int AJLinkArm::write(const IO::Frame&)
{
    return 0;
}

int AJLinkArm::write(const QList<IO::Frame>&)
{
    return 0;
}

void AJLinkArm::do_read()
{
}
