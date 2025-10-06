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

    virtual bool open() = 0;
    virtual bool close() = 0;

    virtual int write(const IO::Frame&) = 0;
    virtual int write(const QList<IO::Frame>&) = 0;

    int getReadCount() const { return rCount; }
    int getWriteCount() const { return wCount; }
    int getErrorCount() const { return eCount; }

    int getReadBufferNum() const { return rBuffer.size(); }

    int getWriteBufferNum() const { return wBuffer.size(); }

    IO::Config getConfig()const{ return config;}
    void setConfig(const IO::Config& config){ this->config=config;}
    QString getName()const{ return name;}

    QList<IO::Frame> readALL() {
        QList<IO::Frame> d;
        d.swap(rBuffer);  // 交换内容
        return d;         // 返回 d


        //return std::exchange(rBuffer, {});

    };
    void setReadReadyCallback(std::function<void(int)> ptr){_readReadyCallback=std::move(ptr);};
protected:
    virtual void run() =0;
    void _readReady(const QList<IO::Frame>& frames)
    {
        rCount += frames.size();
        rBuffer.append(frames);
        if (_readReadyCallback)
        {
            _readReadyCallback(rBuffer.size());
        }
    };
protected:
    IO::Config config;
private:
    QList<IO::Frame> rBuffer;
    QList<IO::Frame> wBuffer;
    int rCount=0;
    int wCount=0;
    int eCount=0;
    uint rSzie=0;
    uint wSzie=0;
    uint eSzie=0;

    const QString name;
    std::function<void(int)> _readReadyCallback=nullptr;
};

QT_BEGIN_NAMESPACE
#define IOInterface_Id "IO.Plugin.Base"
Q_DECLARE_INTERFACE(IOInterface, IOInterface_Id);
QT_END_NAMESPACE



#endif //IOINTERFACE_H
