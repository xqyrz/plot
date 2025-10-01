//
// Created by 25137 on 25-10-1.
//

#ifndef IOINTERFACE_H
#define IOINTERFACE_H
#include  <QObject>
#include <utility>
#include "iocommon.h"
class IOInterface
{
public:
    explicit IOInterface(const QString &name,IO::Config con):config(std::move(con)),name(name){};
    virtual ~IOInterface()=default;

    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual QList<IO::Frame> readALL() = 0;
    virtual int write(const QList<IO::Frame>&) = 0;
    int getReadCount() const { return rCount; }
    int getWriteCount() const { return wCount; }
    int getErrorCount() const { return errorCount; }

    int getReadBufferNum() const { return rBuffer.size(); }

    int getWriteBufferNum() const { return wBuffer.size(); }

    IO::Config getConfig()const{ return config;}
    void setConfig(const IO::Config& config){ this->config=config;}
    QString getName()const{ return name;}
protected:
    virtual void run() =0;
protected:
    QList<IO::Frame> rBuffer;
    QList<IO::Frame> wBuffer;
    int rCount=0;
    int wCount=0;
    int errorCount=0;

    IO::Config config;
    const QString name;
};

QT_BEGIN_NAMESPACE
#define IOInterface_Id "IO.Plugin.Base"
Q_DECLARE_INTERFACE(IOInterface, IOInterface_Id);
QT_END_NAMESPACE



#endif //IOINTERFACE_H
