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
            auto fun =[](IOAPP::SIGNALS& sig,uint64_t id,std::string name,double value) {
                sig.ID.id = id;
                sig.name =name;
                sig.value =value;
            };
            auto msgId = rcv_msg.msgid;
            switch (msgId) {
                case MAVLINK_MSG_ID_sensor: {
                        mavlink_sensor_t sb;
                        mavlink_msg_sensor_decode(&rcv_msg, &sb);
                        qDebug()  << "sensor1=" << sb.sensor1;
                        break;
                }
                case MAVLINK_MSG_ID_gyroscope: {
                    mavlink_gyroscope_t sb;
                    mavlink_msg_gyroscope_decode(&rcv_msg, &sb);
                    //qDebug()  << QString("x:%1 y:%2 z:%3").arg(sb.ACC_X).arg(sb.ACC_Y).arg(sb.ACC_Z);
                    auto sig=getSignal(IOAPP::SELFIO_ID);
                    fun(sig,msgId<<16|1,"GYRO_X", sb.GYRO_X);
                    list.append(sig);

                    fun(sig,msgId<<16|2,"GYRO_Y", sb.GYRO_Y);
                    list.append(sig);

                    fun(sig,msgId<<16|3,"GYRO_Z", sb.GYRO_Z);
                    list.append(sig);

                }
                    break;
                case MAVLINK_MSG_ID_accelerometer: {
                    mavlink_accelerometer_t sb;
                    mavlink_msg_accelerometer_decode(&rcv_msg, &sb);
                    //qDebug()  << QString("x:%1 y:%2 z:%3").arg(sb.ACC_X).arg(sb.ACC_Y).arg(sb.ACC_Z);
                    auto sig=getSignal(IOAPP::SELFIO_ID);
                    fun(sig,msgId<<16|1,"ACC_X", sb.ACC_X);
                    list.append(sig);

                    fun(sig,msgId<<16|2,"ACC_Y", sb.ACC_Y);
                    list.append(sig);

                    fun(sig,msgId<<16|3,"ACC_Z", sb.ACC_Z);
                    list.append(sig);

                }
                    break;
                case MAVLINK_MSG_ID_magnetometer: {
                    mavlink_magnetometer_t sb;
                    mavlink_msg_magnetometer_decode(&rcv_msg, &sb);
                   // qDebug()  << QString("x:%1 y:%2 z:%3").arg(sb.MAG_X).arg(sb.MAG_Y).arg(sb.MAG_Z);
                    auto sig=getSignal(IOAPP::SELFIO_ID);
                    fun(sig,msgId<<16|1,"MAG_X", sb.MAG_X);
                    list.append(sig);

                    fun(sig,msgId<<16|2,"MAG_Y", sb.MAG_Y);
                    list.append(sig);

                    fun(sig,msgId<<16|3,"MAG_Z", sb.MAG_Z);
                    list.append(sig);

                }
                    break;
                case MAVLINK_MSG_ID_TiltSensor: {
                    mavlink_tiltsensor_t sb;
                    mavlink_msg_tiltsensor_decode(&rcv_msg, &sb);
                    // qDebug()  << QString("x:%1 y:%2 z:%3").arg(sb.MAG_X).arg(sb.MAG_Y).arg(sb.MAG_Z);
                    auto sig=getSignal(IOAPP::SELFIO_ID);
                    fun(sig,msgId<<16|1,"Tilt_X", sb.Tilt_X);
                    list.append(sig);

                    fun(sig,msgId<<16|2,"Tilt_Y", sb.Tilt_Y);
                    list.append(sig);
                }
               break;
                case MAVLINK_MSG_ID_OrientationSensor: {
                    mavlink_orientationsensor_t sb;
                    mavlink_msg_orientationsensor_decode(&rcv_msg, &sb);
                    // qDebug()  << QString("x:%1 y:%2 z:%3").arg(sb.MAG_X).arg(sb.MAG_Y).arg(sb.MAG_Z);
                    auto sig=getSignal(IOAPP::SELFIO_ID);
                    fun(sig,msgId<<16|1,"Orientation", sb.Orientation);
                    list.append(sig);
                }
                    break;
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
