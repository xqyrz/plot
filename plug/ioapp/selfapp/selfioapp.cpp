//
// Created by hw on 2025/10/2.
//

#include "selfioapp.h"
#include <QDebug>


SelfIOAPP::SelfIOAPP( QObject* parent): QObject(parent)
,IOAPPInterface()
{

}

QList<IOAPP::SIGNALS>  SelfIOAPP::decode(const IO::Frame& frame)
{
    int i = 0;
    QList<IOAPP::SIGNALS> list;
    auto buf = frame.data.constData();
    while (i<frame.data.size())
    {
        if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &rcv_msg, &status)) {
            // 返回 true 表示一个完整消息已解析完成
//           qDebug() << "Message received, id=" << rcv_msg.msgid;

            // 根据 msgid 处理具体消息
            switch (rcv_msg.msgid) {
                case MAVLINK_MSG_ID_sensor: {
                        mavlink_sensor_t sb;
                        mavlink_msg_sensor_decode(&rcv_msg, &sb);
                        qDebug()  << "sensor1=" << sb.sensor1;
                        break;
                }
                case MAVLINK_MSG_ID_accelerometer: {
                    mavlink_accelerometer_t sb;
                    mavlink_msg_accelerometer_decode(&rcv_msg, &sb);
                    qDebug()  << QString("x:%1 y:%2 z:%3").arg(sb.ACC_X).arg(sb.ACC_Y).arg(sb.ACC_Z);
                    IOAPP::SIGNALS sig;
                    sig.time = QDateTime::currentDateTime();
                    sig.id = 0;
                    sig.value = sb.ACC_X;
                    list.append(sig);

                    sig.id = 1;
                    sig.value = sb.ACC_Y;
                    list.append(sig);

                    sig.id = 2;
                    sig.value = sb.ACC_Z;
                    list.append(sig);
                    break;
                }

            default:break;
            }
        }
        i++;
    }
    return list;
}
IO::Frame SelfIOAPP::encode()
{
    IO::Frame frame;
    mavlink_message_t msg;
    mavlink_sensor_t sb;
    sb.sensor1 = 12345.678;
    mavlink_msg_sensor_encode(sys_id, comp_id,&msg, &sb);
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buffer,&msg);
    frame.data = QByteArray((char*)buffer,len);
    return frame;
}