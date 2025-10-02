//
// Created by hw on 2025/10/2.
//

#ifndef PLOT_IOAPPINTERFACE_H
#define PLOT_IOAPPINTERFACE_H
#include "ioappcommon.h"
#include "../io/iointerface.h"
#include <QObject>
class IOAPPInterface
{
public:

    virtual QList<IOAPP::SIGNALS> decode(const IO::Frame& data) = 0;
    virtual IO::Frame encode()  = 0;
protected:
    QList<QByteArray> m_data;
};

QT_BEGIN_NAMESPACE
#define IOAPPInterface_Id "IOAPP.Plugin.Base"
Q_DECLARE_INTERFACE(IOAPPInterface, IOAPPInterface_Id);
QT_END_NAMESPACE
#endif //PLOT_IOAPPINTERFACE_H
