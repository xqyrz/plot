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
}

QList<IOAPP::SIGNALS>  VOFAAPP::decode(const IO::Frame& frame)
{

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
        buffer.append(buf[i]);
        if (buffer.back() == (char)('\n'))
        {
            if (buffer.contains(','))
            {
                auto sigs = buffer.split(',');
                int cnt =1;
                for (auto & sig:sigs)
                {
                    auto s = getSignalData();
                    s.time = frame.time.toMSecsSinceEpoch();
                    s.value = sig.toDouble();
                    s.name = "vofa_"+std::to_string(cnt);

                    s.ID.id = cnt++;
                   // qDebug()<<QString::fromStdString(s.name)<<s.value;
                    list.append(s);
                }
            }

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
void VOFAAPP::rx_frame(const IO::Frame& frame)
{
    decode(frame);
}
