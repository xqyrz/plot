//
// Created by 25137 on 25-10-1.
//

#ifndef IOINTERFACE_H
#define IOINTERFACE_H
#include  <QObject>
#include <utility>
#include <set>
#include "../interfacebase.h"
#include "bus/bus.h"
#include "iocommon.h"
#include <QDebug>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
class IOInterface:public InterfaceBase
{
public:
    enum
    {
        O_RX = 0
    };
    explicit IOInterface(const QString& name, IO::Config con) : config(std::move(con)), name(name)
    {
        qRegisterMetaType<IO::Frame>("IO::Frame");
        qRegisterMetaType<IO::Frame>("const IO::Frame&");
        qRegisterMetaType<IO::Frame>("const QList<IOAPP::SIGNALS>");
        qRegisterMetaType<IO::Frame>("const QList<IOAPP::SIGNALS>&");
    };
    ~IOInterface() = default;
    virtual bool open() = 0;
    virtual bool close() = 0;

    virtual int write(const IO::Frame&) = 0;
    virtual int write(const QList<IO::Frame>&) = 0;
    const char* getSignal(int index) const override;
    const char* getSlot(int index) const override;
    int getReadCount() const { return rCount; }
    int getWriteCount() const { return wCount; }
    int getErrorCount() const { return eCount; }

    int getReadBufferNum() const { return rBuffer.size(); }

    int getWriteBufferNum() const { return wBuffer.size(); }

    IO::Config _getConfig() const { return config; }
    void _setConfig(const IO::Config& config) { this->config = config; }

    QString getName() const { return name; }

    QList<IO::Frame> readALL()
    {
        QList<IO::Frame> d;
        d.swap(rBuffer); // 交换内容
        return d; // 返回 d


        // return std::exchange(rBuffer, {});
    };
    bool addCallback(int index, const std::function<void(const IO::Frame&)> &ptr)
    {
        switch (index)
        {
        case 0:
            _readReadyCallback.push_back(ptr);
            return true;
        default:
            return false;
        }
    };
    void clearReadReadyCallback() { _readReadyCallback.clear(); };
    void setBus(BUS* bus){m_bus =bus;};
protected:
    virtual void run() = 0;

    void _readReady(const QList<IO::Frame>& frames)
    {
        rCount += frames.size();
        rBuffer.append(frames);
        for (auto frame : rBuffer)
        {
            for (auto& fun : _readReadyCallback)
            {

                fun(frame);
            }
        }
        if (m_bus) m_bus->readIO(rBuffer);
        rBuffer.clear();
    };

protected:
    IO::Config config;

    BUS* m_bus = nullptr;
private:
    QList<IO::Frame> rBuffer;
    QList<IO::Frame> wBuffer;
    int rCount = 0;
    int wCount = 0;
    int eCount = 0;
    uint rSzie = 0;
    uint wSzie = 0;
    uint eSzie = 0;

    const QString name;
    struct readFunctionComparator
    {
        bool operator()(const std::function<void(const IO::Frame&)>& lhs,
                        const std::function<void(const IO::Frame&)>& rhs) const
        {
            // 通过目标地址比较
            return lhs.target<void(const IO::Frame&)>() !=rhs.target<void(const IO::Frame&)>();
        }
    };
    std::list<std::function<void(const IO::Frame&)>> _readReadyCallback;

};
inline const char* IOInterface::getSignal(int index) const
{
    switch (index)
    {
    case 0:         return SIGNAL(rx_frame(const IO::Frame&));
    default:
        return nullptr;
    }
}
inline const char* IOInterface::getSlot(int index) const
{
    switch (index)
    {
    case 0:
        return SLOT(tx_frame(const IO::Frame&));
    default:
        return nullptr;
    }
}

class IOInterface_obj:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
public:
    IOInterface_obj(QObject* parent = nullptr) : QObject(parent){};
    void setStatus(int _status)
    {
        m_status = ( IO::STATUS)_status;
        emit statusChanged();
    }
    IO::STATUS status()const{return m_status;}
signals:
    void statusChanged();
private:
    IO::STATUS m_status = IO::CLOSE_STATUS;
};

QT_BEGIN_NAMESPACE
#define IOInterface_Id "IO.Plugin.Base"
Q_DECLARE_INTERFACE(IOInterface, IOInterface_Id);
QT_END_NAMESPACE



#endif //IOINTERFACE_H
