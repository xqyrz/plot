//
// Created by hw on 2025/10/2.
//

#ifndef PLOT_IOAPPINTERFACE_H
#define PLOT_IOAPPINTERFACE_H
#include <QObject>
#include "../interfacebase.h"
#include "../io/iointerface.h"
class IOAPPInterface:public InterfaceBase
{
    Q_OBJECT
public:
    IOAPPInterface(int _id=0 ):InterfaceBase(), id(_id){};
    void getFrame(const PLUG::Frame&);
    virtual QList<PLUG::_SIGNALS> decode(const PLUG::Frame& data) = 0;
    virtual PLUG::Frame encode() = 0;
    inline PLUG::_SIGNALS getSignalData()
    {
        PLUG::_SIGNALS signal;
       // signal.time = QDateTime::currentDateTime().toMSecsSinceEpoch();
        signal.ID.res = 1;
        signal.ID.type = id;

        return signal;
    }
    void addCallback(int index,std::function<void(const QList<PLUG::_SIGNALS>& )> ptr);
protected:
    QList<QByteArray> m_data;
    struct signalFunctionComparator {
        bool operator()(const std::function<void(const  QList<PLUG::_SIGNALS>&)>& lhs,
                        const std::function<void(const  QList<PLUG::_SIGNALS>&)>& rhs) const {
            // 通过目标地址比较
            return lhs.target<void(const  QList<PLUG::_SIGNALS>&)>() < rhs.target<void(const  QList<PLUG::_SIGNALS>&)>();
        }
    };
    std::set<std::function<void(const  QList<PLUG::_SIGNALS>& )>,signalFunctionComparator> _signalCallback;
    const uint32_t id;
};
inline void IOAPPInterface::getFrame(const PLUG::Frame& frame)
{
    auto _signals = this->decode(frame);
    if (_signals.size())
    {
        for (auto& fun : _signalCallback)
        {
            fun(_signals);
        }
    }
}

inline void IOAPPInterface::addCallback(int index,std::function<void(const QList<PLUG::_SIGNALS>& )> ptr)
{
    _signalCallback.insert(ptr);
}


QT_BEGIN_NAMESPACE
#define IOAPPInterface_Id "IOAPP.Plugin.Base"
Q_DECLARE_INTERFACE(IOAPPInterface, IOAPPInterface_Id);
QT_END_NAMESPACE
#endif //PLOT_IOAPPINTERFACE_H
