//
// Created by 25137 on 25-10-1.
//

#ifndef IOINTERFACE_H
#define IOINTERFACE_H
#include <QDebug>
#include <QObject>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <set>
#include <utility>
#include "../interfacebase.h"
#include "bus/bus.h"
class  IOInterface:public InterfaceBase
{
    Q_OBJECT
public:
    enum
    {
        O_RX = 0
    };
    explicit IOInterface(const QString& name, PLUG::Config con) : config(std::move(con))
    {
        m_type = IOInterfaceEnum;
        m_name = name;
        qRegisterMetaType<PLUG::Frame>("IO::Frame");
        qRegisterMetaType<PLUG::Frame>("const IO::Frame&");
        qRegisterMetaType<PLUG::Frame>("const QList<IOAPP::SIGNALS>");
        qRegisterMetaType<PLUG::Frame>("const QList<IOAPP::SIGNALS>&");

        m_inputPorts << PLUG::InputType::IN_IO_RX<< PLUG::InputType::IN_IO_TX;
        m_outputPorts << PLUG::OutputType::OUT_IO_TX<< PLUG::OutputType::OUT_IO_RX;
    };
    ~IOInterface() = default;
    virtual bool open() = 0;
    virtual bool close() = 0;

    virtual int write(const PLUG::Frame&) = 0;
    virtual int write(const QList<PLUG::Frame>&) = 0;
    int getReadCount() const { return rCount; }
    int getWriteCount() const { return wCount; }
    int getErrorCount() const { return eCount; }

    int getReadBufferNum() const { return rBuffer.size(); }

    int getWriteBufferNum() const { return wBuffer.size(); }

    PLUG::Config _getConfig() const { return config; }
    void _setConfig(const PLUG::Config& config) { this->config = config; }



    QList<PLUG::Frame> readALL()
    {
        QList<PLUG::Frame> d;
        d.swap(rBuffer); // 交换内容
        return d; // 返回 d


        // return std::exchange(rBuffer, {});
    };
    bool addCallback(int index, const std::function<void(const PLUG::Frame&)> &ptr)
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
protected:
    virtual void run() = 0;

    void _readReady(const QList<PLUG::Frame>& frames)
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
        rBuffer.clear();
    };

protected:
    PLUG::Config config;

private:
    QList<PLUG::Frame> rBuffer;
    QList<PLUG::Frame> wBuffer;
    int rCount = 0;
    int wCount = 0;
    int eCount = 0;
    uint rSzie = 0;
    uint wSzie = 0;
    uint eSzie = 0;

    struct readFunctionComparator
    {
        bool operator()(const std::function<void(const PLUG::Frame&)>& lhs,
                        const std::function<void(const PLUG::Frame&)>& rhs) const
        {
            // 通过目标地址比较
            return lhs.target<void(const PLUG::Frame&)>() !=rhs.target<void(const PLUG::Frame&)>();
        }
    };
    std::list<std::function<void(const PLUG::Frame&)>> _readReadyCallback;
private:
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
public:
    // IOInterface_obj(QObject* parent = nullptr) : QObject(parent){};
    void setStatus(int _status)
    {
        m_status = ( PLUG::STATUS)_status;
        emit statusChanged();
    }
    PLUG::STATUS status()const{return m_status;}
    signals:
        void statusChanged();
private:
    PLUG::STATUS m_status = PLUG::CLOSE_STATUS;
};


//class IOInterface_obj:public QObject
//{
//    Q_OBJECT
//
//};

QT_BEGIN_NAMESPACE
#define IOInterface_Id "IO.Plugin.Base"
Q_DECLARE_INTERFACE(IOInterface, IOInterface_Id);
QT_END_NAMESPACE



#endif //IOINTERFACE_H
