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
    explicit IOInterface(const QString& name, INC::Config con) : config(std::move(con))
    {
        m_type = IOInterfaceEnum;
        m_name = name;
        qRegisterMetaType<INC::Frame>("IO::Frame");
        qRegisterMetaType<INC::Frame>("const IO::Frame&");
        qRegisterMetaType<INC::Frame>("const QList<IOAPP::SIGNALS>");
        qRegisterMetaType<INC::Frame>("const QList<IOAPP::SIGNALS>&");

        m_inputPorts << Plug::InputType::IN_IO_RX<< Plug::InputType::IN_IO_TX;
        m_outputPorts << Plug::OutputType::OUT_IO_TX<< Plug::OutputType::OUT_IO_RX;
    };
    ~IOInterface() = default;
    virtual bool open() = 0;
    virtual bool close() = 0;

    virtual int write(const INC::Frame&) = 0;
    virtual int write(const QList<INC::Frame>&) = 0;
    int getReadCount() const { return rCount; }
    int getWriteCount() const { return wCount; }
    int getErrorCount() const { return eCount; }

    int getReadBufferNum() const { return rBuffer.size(); }

    int getWriteBufferNum() const { return wBuffer.size(); }

    INC::Config _getConfig() const { return config; }
    void _setConfig(const INC::Config& config) { this->config = config; }



    QList<INC::Frame> readALL()
    {
        QList<INC::Frame> d;
        d.swap(rBuffer); // 交换内容
        return d; // 返回 d


        // return std::exchange(rBuffer, {});
    };
    bool addCallback(int index, const std::function<void(const INC::Frame&)> &ptr)
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

    void _readReady(const QList<INC::Frame>& frames)
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
    INC::Config config;

private:
    QList<INC::Frame> rBuffer;
    QList<INC::Frame> wBuffer;
    int rCount = 0;
    int wCount = 0;
    int eCount = 0;
    uint rSzie = 0;
    uint wSzie = 0;
    uint eSzie = 0;

    struct readFunctionComparator
    {
        bool operator()(const std::function<void(const INC::Frame&)>& lhs,
                        const std::function<void(const INC::Frame&)>& rhs) const
        {
            // 通过目标地址比较
            return lhs.target<void(const INC::Frame&)>() !=rhs.target<void(const INC::Frame&)>();
        }
    };
    std::list<std::function<void(const INC::Frame&)>> _readReadyCallback;
private:
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
public:
    // IOInterface_obj(QObject* parent = nullptr) : QObject(parent){};
    void setStatus(int _status)
    {
        m_status = ( INC::STATUS)_status;
        emit statusChanged();
    }
    INC::STATUS status()const{return m_status;}
    signals:
        void statusChanged();
private:
    INC::STATUS m_status = INC::CLOSE_STATUS;
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
