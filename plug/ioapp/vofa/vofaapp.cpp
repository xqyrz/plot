//
// Created by hw on 2025/10/2.
//

#include "vofaapp.h"
#include <QDebug>


VOFAAPP::VOFAAPP( QObject* parent): QObject(parent)
,IOAPPInterface(IOAPP::VAFA_ID)
,_last(QTime::currentTime())
{
    addCallback(0,[this]( const QList<IOAPP::SIGNALS>& _signals)
    {
        emit hasSignal(_signals);
    });
    for (int i=0;i<10;i++)
    {
        sigNames.append("vofa_"+QString::number(i+1));
    }
}

QList<IOAPP::SIGNALS>  VOFAAPP::decode(const IO::Frame& frame)
{
    auto last = buffer;
    int i = 0;
    QList<IOAPP::SIGNALS> list;
    auto time = QTime::currentTime();
    if (_last.msecsTo(time)>200)
    {

        buffer.clear();
    }
    _last = time;
    auto buf = frame.data.constData();
    
    while (i<frame.data.size())
    {
       //TODO
        double d = frame.time.toMSecsSinceEpoch();
        if (buf[i] != '\n')
        {
            buffer.append(buf[i]);
        }
        else
        {
            if (buffer.contains(','))
            {
                auto sigs = buffer.split(',');
                int cnt =0;
                for (auto & sig:sigs)
                {
                    auto s = getSignalData();
                    s.time =d;
                    s.value = sig.toDouble();
                    s.name = sigNames.at(cnt).toStdString();
                    s.ID.id = cnt++;
                   //qDebug()<<QString::fromStdString(s.name)<<s.value;
                    list.append(s);
                }
            }
            d +=0.2;
            buffer.clear();
        }
        i++;
    }
    emit hasSignal(list);

    return list;
}
IO::Frame VOFAAPP::encode()
{
    IO::Frame frame;

    return frame;
}
QList<std::tuple<QVariant::Type, QString, QVariant>> VOFAAPP::getConfig()
{
    QList<std::tuple<QVariant::Type, QString, QVariant>> temp;
    int i = 0;
    for (auto& var : sigNames)
    {
        i++;
        temp.append(std::make_tuple(QVariant::String, QString("signal_") + QString::number(i), var));
    }
    return temp;
}
void VOFAAPP::setConfig(const QList<std::tuple<QVariant::Type, QString, QVariant>>& tuples)
{
    for (auto& var : tuples)
    {
        auto index = std::get<1>(var).split('_').at(1).toInt() - 1;
        sigNames[index] = std::get<2>(var).toString();
    }
}

void VOFAAPP::rx_frame(const IO::Frame& frame)
{
    decode(frame);
}
