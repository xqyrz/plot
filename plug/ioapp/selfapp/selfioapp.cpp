//
// Created by hw on 2025/10/2.
//

#include "selfioapp.h"
#include <QDebug>


SelfIOAPP::SelfIOAPP( QObject* parent): QObject(parent)
,IOAPPInterface()
{

}

int SelfIOAPP::decode(const IO::Frame& frame)
{
    int i = 0;
    auto buf = frame.data.constData();
    while (i<frame.data.size())
    {
        if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &rcv_msg, &status)) {
            // 返回 true 表示一个完整消息已解析完成
           qDebug() << "Message received, id=" << rcv_msg.msgid;

            // 根据 msgid 处理具体消息
            switch (rcv_msg.msgid) {
                case MAVLINK_MSG_ID_sensor: {
                        mavlink_sensor_t sb;
                        mavlink_msg_sensor_decode(&rcv_msg, &sb);
                        qDebug()  << "sensor1=" << sb.sensor1;
                        break;
                }
            default:break;
            }
        }
        i++;
    }
    return 0;
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