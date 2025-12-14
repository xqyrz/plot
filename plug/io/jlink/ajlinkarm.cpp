#include "ajlinkarm.h"


AJLinkArm::AJLinkArm(IO::Config config, QObject* parent)
    :QObject(parent)
    ,IOInterface("aJlinkArm", config)
{
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
