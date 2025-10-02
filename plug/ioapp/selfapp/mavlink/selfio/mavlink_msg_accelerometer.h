#pragma once
// MESSAGE accelerometer PACKING

#define MAVLINK_MSG_ID_accelerometer 56102


typedef struct __mavlink_accelerometer_t {
 double ACC_X; /*<  ACC_X*/
 double ACC_Y; /*<  ACC_Y*/
 double ACC_Z; /*<  ACC_Z*/
} mavlink_accelerometer_t;

#define MAVLINK_MSG_ID_accelerometer_LEN 24
#define MAVLINK_MSG_ID_accelerometer_MIN_LEN 24
#define MAVLINK_MSG_ID_56102_LEN 24
#define MAVLINK_MSG_ID_56102_MIN_LEN 24

#define MAVLINK_MSG_ID_accelerometer_CRC 185
#define MAVLINK_MSG_ID_56102_CRC 185



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_accelerometer { \
    56102, \
    "accelerometer", \
    3, \
    {  { "ACC_X", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_accelerometer_t, ACC_X) }, \
         { "ACC_Y", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_accelerometer_t, ACC_Y) }, \
         { "ACC_Z", NULL, MAVLINK_TYPE_DOUBLE, 0, 16, offsetof(mavlink_accelerometer_t, ACC_Z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_accelerometer { \
    "accelerometer", \
    3, \
    {  { "ACC_X", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_accelerometer_t, ACC_X) }, \
         { "ACC_Y", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_accelerometer_t, ACC_Y) }, \
         { "ACC_Z", NULL, MAVLINK_TYPE_DOUBLE, 0, 16, offsetof(mavlink_accelerometer_t, ACC_Z) }, \
         } \
}
#endif

/**
 * @brief Pack a accelerometer message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param ACC_X  ACC_X
 * @param ACC_Y  ACC_Y
 * @param ACC_Z  ACC_Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_accelerometer_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double ACC_X, double ACC_Y, double ACC_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_accelerometer_LEN];
    _mav_put_double(buf, 0, ACC_X);
    _mav_put_double(buf, 8, ACC_Y);
    _mav_put_double(buf, 16, ACC_Z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_accelerometer_LEN);
#else
    mavlink_accelerometer_t packet;
    packet.ACC_X = ACC_X;
    packet.ACC_Y = ACC_Y;
    packet.ACC_Z = ACC_Z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_accelerometer_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_accelerometer;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_accelerometer_MIN_LEN, MAVLINK_MSG_ID_accelerometer_LEN, MAVLINK_MSG_ID_accelerometer_CRC);
}

/**
 * @brief Pack a accelerometer message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param ACC_X  ACC_X
 * @param ACC_Y  ACC_Y
 * @param ACC_Z  ACC_Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_accelerometer_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double ACC_X, double ACC_Y, double ACC_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_accelerometer_LEN];
    _mav_put_double(buf, 0, ACC_X);
    _mav_put_double(buf, 8, ACC_Y);
    _mav_put_double(buf, 16, ACC_Z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_accelerometer_LEN);
#else
    mavlink_accelerometer_t packet;
    packet.ACC_X = ACC_X;
    packet.ACC_Y = ACC_Y;
    packet.ACC_Z = ACC_Z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_accelerometer_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_accelerometer;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_accelerometer_MIN_LEN, MAVLINK_MSG_ID_accelerometer_LEN, MAVLINK_MSG_ID_accelerometer_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_accelerometer_MIN_LEN, MAVLINK_MSG_ID_accelerometer_LEN);
#endif
}

/**
 * @brief Pack a accelerometer message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ACC_X  ACC_X
 * @param ACC_Y  ACC_Y
 * @param ACC_Z  ACC_Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_accelerometer_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double ACC_X,double ACC_Y,double ACC_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_accelerometer_LEN];
    _mav_put_double(buf, 0, ACC_X);
    _mav_put_double(buf, 8, ACC_Y);
    _mav_put_double(buf, 16, ACC_Z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_accelerometer_LEN);
#else
    mavlink_accelerometer_t packet;
    packet.ACC_X = ACC_X;
    packet.ACC_Y = ACC_Y;
    packet.ACC_Z = ACC_Z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_accelerometer_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_accelerometer;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_accelerometer_MIN_LEN, MAVLINK_MSG_ID_accelerometer_LEN, MAVLINK_MSG_ID_accelerometer_CRC);
}

/**
 * @brief Encode a accelerometer struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param accelerometer C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_accelerometer_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_accelerometer_t* accelerometer)
{
    return mavlink_msg_accelerometer_pack(system_id, component_id, msg, accelerometer->ACC_X, accelerometer->ACC_Y, accelerometer->ACC_Z);
}

/**
 * @brief Encode a accelerometer struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param accelerometer C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_accelerometer_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_accelerometer_t* accelerometer)
{
    return mavlink_msg_accelerometer_pack_chan(system_id, component_id, chan, msg, accelerometer->ACC_X, accelerometer->ACC_Y, accelerometer->ACC_Z);
}

/**
 * @brief Encode a accelerometer struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param accelerometer C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_accelerometer_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_accelerometer_t* accelerometer)
{
    return mavlink_msg_accelerometer_pack_status(system_id, component_id, _status, msg,  accelerometer->ACC_X, accelerometer->ACC_Y, accelerometer->ACC_Z);
}

/**
 * @brief Send a accelerometer message
 * @param chan MAVLink channel to send the message
 *
 * @param ACC_X  ACC_X
 * @param ACC_Y  ACC_Y
 * @param ACC_Z  ACC_Z
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_accelerometer_send(mavlink_channel_t chan, double ACC_X, double ACC_Y, double ACC_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_accelerometer_LEN];
    _mav_put_double(buf, 0, ACC_X);
    _mav_put_double(buf, 8, ACC_Y);
    _mav_put_double(buf, 16, ACC_Z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_accelerometer, buf, MAVLINK_MSG_ID_accelerometer_MIN_LEN, MAVLINK_MSG_ID_accelerometer_LEN, MAVLINK_MSG_ID_accelerometer_CRC);
#else
    mavlink_accelerometer_t packet;
    packet.ACC_X = ACC_X;
    packet.ACC_Y = ACC_Y;
    packet.ACC_Z = ACC_Z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_accelerometer, (const char *)&packet, MAVLINK_MSG_ID_accelerometer_MIN_LEN, MAVLINK_MSG_ID_accelerometer_LEN, MAVLINK_MSG_ID_accelerometer_CRC);
#endif
}

/**
 * @brief Send a accelerometer message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_accelerometer_send_struct(mavlink_channel_t chan, const mavlink_accelerometer_t* accelerometer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_accelerometer_send(chan, accelerometer->ACC_X, accelerometer->ACC_Y, accelerometer->ACC_Z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_accelerometer, (const char *)accelerometer, MAVLINK_MSG_ID_accelerometer_MIN_LEN, MAVLINK_MSG_ID_accelerometer_LEN, MAVLINK_MSG_ID_accelerometer_CRC);
#endif
}

#if MAVLINK_MSG_ID_accelerometer_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_accelerometer_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double ACC_X, double ACC_Y, double ACC_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, ACC_X);
    _mav_put_double(buf, 8, ACC_Y);
    _mav_put_double(buf, 16, ACC_Z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_accelerometer, buf, MAVLINK_MSG_ID_accelerometer_MIN_LEN, MAVLINK_MSG_ID_accelerometer_LEN, MAVLINK_MSG_ID_accelerometer_CRC);
#else
    mavlink_accelerometer_t *packet = (mavlink_accelerometer_t *)msgbuf;
    packet->ACC_X = ACC_X;
    packet->ACC_Y = ACC_Y;
    packet->ACC_Z = ACC_Z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_accelerometer, (const char *)packet, MAVLINK_MSG_ID_accelerometer_MIN_LEN, MAVLINK_MSG_ID_accelerometer_LEN, MAVLINK_MSG_ID_accelerometer_CRC);
#endif
}
#endif

#endif

// MESSAGE accelerometer UNPACKING


/**
 * @brief Get field ACC_X from accelerometer message
 *
 * @return  ACC_X
 */
static inline double mavlink_msg_accelerometer_get_ACC_X(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Get field ACC_Y from accelerometer message
 *
 * @return  ACC_Y
 */
static inline double mavlink_msg_accelerometer_get_ACC_Y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  8);
}

/**
 * @brief Get field ACC_Z from accelerometer message
 *
 * @return  ACC_Z
 */
static inline double mavlink_msg_accelerometer_get_ACC_Z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  16);
}

/**
 * @brief Decode a accelerometer message into a struct
 *
 * @param msg The message to decode
 * @param accelerometer C-struct to decode the message contents into
 */
static inline void mavlink_msg_accelerometer_decode(const mavlink_message_t* msg, mavlink_accelerometer_t* accelerometer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    accelerometer->ACC_X = mavlink_msg_accelerometer_get_ACC_X(msg);
    accelerometer->ACC_Y = mavlink_msg_accelerometer_get_ACC_Y(msg);
    accelerometer->ACC_Z = mavlink_msg_accelerometer_get_ACC_Z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_accelerometer_LEN? msg->len : MAVLINK_MSG_ID_accelerometer_LEN;
        memset(accelerometer, 0, MAVLINK_MSG_ID_accelerometer_LEN);
    memcpy(accelerometer, _MAV_PAYLOAD(msg), len);
#endif
}
