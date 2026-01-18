//
// Created by hw on 2025/10/2.
//

#ifndef PLOT_IOAPPINTERFACE_H
#define PLOT_IOAPPINTERFACE_H
#include "ioappcommon.h"
#include "../io/iointerface.h"
#include "../interfacebase.h"
#include <QObject>
class IOAPPInterface:public InterfaceBase
{
public:
    void getFrame(const IO::Frame&);
    virtual QList<IOAPP::SIGNALS> decode(const IO::Frame& data) = 0;
    virtual IO::Frame encode() = 0;
    const char* getSignal(int index) const override;
    const char* getSlot(int index) const override;
    inline IOAPP::SIGNALS getSignalData(uint32_t id)
    {
        IOAPP::SIGNALS signal;
        signal.time = QDateTime::currentDateTime().toMSecsSinceEpoch();
        signal.ID.res = 1;
        signal.ID.type = id;

        return signal;
    }
    void addCallback(int index,std::function<void(const QList<IOAPP::SIGNALS>& )> ptr);
protected:
    QList<QByteArray> m_data;
    struct signalFunctionComparator {
        bool operator()(const std::function<void(const  QList<IOAPP::SIGNALS>&)>& lhs,
                        const std::function<void(const  QList<IOAPP::SIGNALS>&)>& rhs) const {
            // 通过目标地址比较
            return lhs.target<void(const  QList<IOAPP::SIGNALS>&)>() < rhs.target<void(const  QList<IOAPP::SIGNALS>&)>();
        }
    };
    std::set<std::function<void(const  QList<IOAPP::SIGNALS>& )>,signalFunctionComparator> _signalCallback;
};
inline void IOAPPInterface::getFrame(const IO::Frame& frame)
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
inline const char* IOAPPInterface::getSignal(int index) const {
    switch (index)
{
    case 2: return SIGNAL(hasSignal(const QList<IOAPP::SIGNALS>&));
    default: return nullptr;
} }
inline const char* IOAPPInterface::getSlot(int index) const
{
    switch (index)
    {
    case 0: return SLOT(rx_frame(const IO::Frame&));
    default: return nullptr;
    }

}
inline void IOAPPInterface::addCallback(int index,std::function<void(const QList<IOAPP::SIGNALS>& )> ptr)
{
    _signalCallback.insert(ptr);
}


QT_BEGIN_NAMESPACE
#define IOAPPInterface_Id "IOAPP.Plugin.Base"
Q_DECLARE_INTERFACE(IOAPPInterface, IOAPPInterface_Id);
QT_END_NAMESPACE
#endif //PLOT_IOAPPINTERFACE_H
