//
// Created by hw on 2025/10/2.
//

#include "selfioapp.h"
#include <QDebug>


SelfIOAPP::SelfIOAPP( QObject* parent): QObject(parent)
,IOAPPInterface()
{

}

int SelfIOAPP::decode(QByteArray& data)
{
    int i = 0;
    auto buf = data.constData();
    while (i<data.size())
    {
        if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &rcv_msg, &status)) {
            // 返回 true 表示一个完整消息已解析完成
           qDebug() << "Message received, id=" << rcv_msg.msgid;

            // 根据 msgid 处理具体消息
            switch (rcv_msg.msgid) {
                case MAVLINK_MSG_ID_sensor: {
                        mavlink_sensor_t sb;
                        mavlink_msg_sensor_decode(&rcv_msg, &sb);
                        qDebug()  << "sensor1=" << (int)sb.sensor1;
                        break;
                }
            default:break;
            }
        }
    }
    return 0;
}
int SelfIOAPP::encode(QByteArray& data)
{

    return 0;
}