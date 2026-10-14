#include "ajlinkarm.h"
#include "jlinkarm.h"
#include <QTimer>
AJLinkArm::AJLinkArm(INC::Config config, QObject* parent)
    :IOInterface("aJlinkArm", config)
    ,_handle(new JlinkARM())
,timer(new QTimer(this))
{
    qDebug()<<"version:"<<_handle->jlinkGetDLLVersionFunc();
    addCallback(0,[this](const INC::Frame& frame)
{
    emit rx_frame(frame);
});
    connect(timer,&QTimer::timeout,[this]()
    {
        unsigned int addr = 0x2000041c;
        union
        {
            float f;
            unsigned int u32;
        } value;
        int ret = _handle->jlinkReadMemFunc(addr, 4,&(value.u32));
        if (ret == 0)
        {
            qDebug() << "Address 0x" << QString::number(addr, 16)
                     << value.f;
        }
        else
        {
            qDebug() << "Read failed, error code:" << ret;
        }
    });
}

AJLinkArm::~AJLinkArm()
{
    delete _handle;
}

void AJLinkArm::run()
{

timer->start(50);
}

bool AJLinkArm::open()
{
    if (_handle->jlinkIsOpen())
    {
        _handle->jlinkClose();
    }
   qDebug()<< _handle->jlinkOpen();

    if(_handle->jlinkExecCommandFunc(QString("device=STM32G431CB").toUtf8().data(),0,0)){
       qWarning()<< QString("<font color='red'>设置mcu为 %1 失败，检查连接</font>").arg("STM32G431CB");
        return false;
    }
    else{
       // emit info((QString("device=%1").arg(CPU).toUtf8().data()));
    }
    if(_handle->jlinkTIFSelectFunc(JlinkARM::JLINKARM_TIF_SWD))
    {
    //    emit errInfo(swd_not);
        qWarning()<< QString("<font color='red'>设置SWD模式失败</font>");
        _handle->jlinkClose();
        return false;
    }
    else{
      //  emit info(QString("SWD模式"));
    }
    _handle->jlinkSetSpeedFunc(4000);
    if(_handle->jlinkConnectFunc()){
       qWarning()<< QString("<font color='red'>设置mcu速率为 %1kb 失败，检查连接</font>")
        .arg(4000);
        _handle->jlinkClose();
        return false;
    }
    else{
      //  emit info("speed  "+QString::number(this->speed?1000:4000)+"kb");
    }
    if(!_handle->jlinkIsConnectedFunc()){
      //  emit errInfo(cpu_connectFaild);
        qWarning()<< QString("<font color='red'>连接失败</font>");
        _handle->jlinkClose();
    }
    else{
       // emit info("connect success");
    }
    qDebug()<<"SN : "<< _handle->jlinkGetSNFunc();
    qDebug()<<"HV : "<< _handle->jlinkGetHardwareVersionFunc();
    qDebug()<<"ID : "<< _handle->jlinkGetIdFunc();
    qDebug()<<"CID: "<< _handle->jlinkGetCoreIdFunc();
    qDebug()<<"SPE: "<< _handle->jlinkGetSpeedFunc();
    char buf[1024];
    _handle->jlinkGetFirmwareStringFunc(buf,sizeof(buf));
    _handle->jlinkExecCommandFunc("ShowEmuInfo", 0, 0);
    qDebug()<<"Firmware: "<<buf;


    return false;
}

bool AJLinkArm::close()
{
    return false;
}

int AJLinkArm::write(const INC::Frame&)
{
    return 0;
}

int AJLinkArm::write(const QList<INC::Frame>&)
{
    return 0;
}

void AJLinkArm::do_read()
{
}
