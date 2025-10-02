#pragma once
// MESSAGE magnetometer PACKING

#define MAVLINK_MSG_ID_magnetometer 56104


typedef struct __mavlink_magnetometer_t {
 double MAG_X; /*<  MAG_X*/
 double MAG_Y; /*<  MAG_Y*/
 double MAG_Z; /*<  MAG_Z*/
} mavlink_magnetometer_t;

#define MAVLINK_MSG_ID_magnetometer_LEN 24
#define MAVLINK_MSG_ID_magnetometer_MIN_LEN 24
#define MAVLINK_MSG_ID_56104_LEN 24
#define MAVLINK_MSG_ID_56104_MIN_LEN 24

#define MAVLINK_MSG_ID_magnetometer_CRC 144
#define MAVLINK_MSG_ID_56104_CRC 144



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_magnetometer { \
    56104, \
    "magnetometer", \
    3, \
    {  { "MAG_X", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_magnetometer_t, MAG_X) }, \
         { "MAG_Y", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_magnetometer_t, MAG_Y) }, \
         { "MAG_Z", NULL, MAVLINK_TYPE_DOUBLE, 0, 16, offsetof(mavlink_magnetometer_t, MAG_Z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_magnetometer { \
    "magnetometer", \
    3, \
    {  { "MAG_X", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_magnetometer_t, MAG_X) }, \
         { "MAG_Y", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_magnetometer_t, MAG_Y) }, \
         { "MAG_Z", NULL, MAVLINK_TYPE_DOUBLE, 0, 16, offsetof(mavlink_magnetometer_t, MAG_Z) }, \
         } \
}
#endif

/**
 * @brief Pack a magnetometer message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param MAG_X  MAG_X
 * @param MAG_Y  MAG_Y
 * @param MAG_Z  MAG_Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_magnetometer_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double MAG_X, double MAG_Y, double MAG_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_magnetometer_LEN];
    _mav_put_double(buf, 0, MAG_X);
    _mav_put_double(buf, 8, MAG_Y);
    _mav_put_double(buf, 16, MAG_Z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_magnetometer_LEN);
#else
    mavlink_magnetometer_t packet;
    packet.MAG_X = MAG_X;
    packet.MAG_Y = MAG_Y;
    packet.MAG_Z = MAG_Z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_magnetometer_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_magnetometer;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_magnetometer_MIN_LEN, MAVLINK_MSG_ID_magnetometer_LEN, MAVLINK_MSG_ID_magnetometer_CRC);
}

/**
 * @brief Pack a magnetometer message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param MAG_X  MAG_X
 * @param MAG_Y  MAG_Y
 * @param MAG_Z  MAG_Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_magnetometer_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double MAG_X, double MAG_Y, double MAG_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_magnetometer_LEN];
    _mav_put_double(buf, 0, MAG_X);
    _mav_put_double(buf, 8, MAG_Y);
    _mav_put_double(buf, 16, MAG_Z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_magnetometer_LEN);
#else
    mavlink_magnetometer_t packet;
    packet.MAG_X = MAG_X;
    packet.MAG_Y = MAG_Y;
    packet.MAG_Z = MAG_Z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_magnetometer_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_magnetometer;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_magnetometer_MIN_LEN, MAVLINK_MSG_ID_magnetometer_LEN, MAVLINK_MSG_ID_magnetometer_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_magnetometer_MIN_LEN, MAVLINK_MSG_ID_magnetometer_LEN);
#endif
}

/**
 * @brief Pack a magnetometer message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param MAG_X  MAG_X
 * @param MAG_Y  MAG_Y
 * @param MAG_Z  MAG_Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_magnetometer_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double MAG_X,double MAG_Y,double MAG_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_magnetometer_LEN];
    _mav_put_double(buf, 0, MAG_X);
    _mav_put_double(buf, 8, MAG_Y);
    _mav_put_double(buf, 16, MAG_Z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_magnetometer_LEN);
#else
    mavlink_magnetometer_t packet;
    packet.MAG_X = MAG_X;
    packet.MAG_Y = MAG_Y;
    packet.MAG_Z = MAG_Z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_magnetometer_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_magnetometer;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_magnetometer_MIN_LEN, MAVLINK_MSG_ID_magnetometer_LEN, MAVLINK_MSG_ID_magnetometer_CRC);
}

/**
 * @brief Encode a magnetometer struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param magnetometer C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_magnetometer_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_magnetometer_t* magnetometer)
{
    return mavlink_msg_magnetometer_pack(system_id, component_id, msg, magnetometer->MAG_X, magnetometer->MAG_Y, magnetometer->MAG_Z);
}

/**
 * @brief Encode a magnetometer struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param magnetometer C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_magnetometer_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_magnetometer_t* magnetometer)
{
    return mavlink_msg_magnetometer_pack_chan(system_id, component_id, chan, msg, magnetometer->MAG_X, magnetometer->MAG_Y, magnetometer->MAG_Z);
}

/**
 * @brief Encode a magnetometer struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param magnetometer C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_magnetometer_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_magnetometer_t* magnetometer)
{
    return mavlink_msg_magnetometer_pack_status(system_id, component_id, _status, msg,  magnetometer->MAG_X, magnetometer->MAG_Y, magnetometer->MAG_Z);
}

/**
 * @brief Send a magnetometer message
 * @param chan MAVLink channel to send the message
 *
 * @param MAG_X  MAG_X
 * @param MAG_Y  MAG_Y
 * @param MAG_Z  MAG_Z
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_magnetometer_send(mavlink_channel_t chan, double MAG_X, double MAG_Y, double MAG_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_magnetometer_LEN];
    _mav_put_double(buf, 0, MAG_X);
    _mav_put_double(buf, 8, MAG_Y);
    _mav_put_double(buf, 16, MAG_Z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_magnetometer, buf, MAVLINK_MSG_ID_magnetometer_MIN_LEN, MAVLINK_MSG_ID_magnetometer_LEN, MAVLINK_MSG_ID_magnetometer_CRC);
#else
    mavlink_magnetometer_t packet;
    packet.MAG_X = MAG_X;
    packet.MAG_Y = MAG_Y;
    packet.MAG_Z = MAG_Z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_magnetometer, (const char *)&packet, MAVLINK_MSG_ID_magnetometer_MIN_LEN, MAVLINK_MSG_ID_magnetometer_LEN, MAVLINK_MSG_ID_magnetometer_CRC);
#endif
}

/**
 * @brief Send a magnetometer message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_magnetometer_send_struct(mavlink_channel_t chan, const mavlink_magnetometer_t* magnetometer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_magnetometer_send(chan, magnetometer->MAG_X, magnetometer->MAG_Y, magnetometer->MAG_Z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_magnetometer, (const char *)magnetometer, MAVLINK_MSG_ID_magnetometer_MIN_LEN, MAVLINK_MSG_ID_magnetometer_LEN, MAVLINK_MSG_ID_magnetometer_CRC);
#endif
}

#if MAVLINK_MSG_ID_magnetometer_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_magnetometer_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double MAG_X, double MAG_Y, double MAG_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, MAG_X);
    _mav_put_double(buf, 8, MAG_Y);
    _mav_put_double(buf, 16, MAG_Z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_magnetometer, buf, MAVLINK_MSG_ID_magnetometer_MIN_LEN, MAVLINK_MSG_ID_magnetometer_LEN, MAVLINK_MSG_ID_magnetometer_CRC);
#else
    mavlink_magnetometer_t *packet = (mavlink_magnetometer_t *)msgbuf;
    packet->MAG_X = MAG_X;
    packet->MAG_Y = MAG_Y;
    packet->MAG_Z = MAG_Z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_magnetometer, (const char *)packet, MAVLINK_MSG_ID_magnetometer_MIN_LEN, MAVLINK_MSG_ID_magnetometer_LEN, MAVLINK_MSG_ID_magnetometer_CRC);
#endif
}
#endif

#endif

// MESSAGE magnetometer UNPACKING


/**
 * @brief Get field MAG_X from magnetometer message
 *
 * @return  MAG_X
 */
static inline double mavlink_msg_magnetometer_get_MAG_X(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Get field MAG_Y from magnetometer message
 *
 * @return  MAG_Y
 */
static inline double mavlink_msg_magnetometer_get_MAG_Y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  8);
}

/**
 * @brief Get field MAG_Z from magnetometer message
 *
 * @return  MAG_Z
 */
static inline double mavlink_msg_magnetometer_get_MAG_Z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  16);
}

/**
 * @brief Decode a magnetometer message into a struct
 *
 * @param msg The message to decode
 * @param magnetometer C-struct to decode the message contents into
 */
static inline void mavlink_msg_magnetometer_decode(const mavlink_message_t* msg, mavlink_magnetometer_t* magnetometer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    magnetometer->MAG_X = mavlink_msg_magnetometer_get_MAG_X(msg);
    magnetometer->MAG_Y = mavlink_msg_magnetometer_get_MAG_Y(msg);
    magnetometer->MAG_Z = mavlink_msg_magnetometer_get_MAG_Z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_magnetometer_LEN? msg->len : MAVLINK_MSG_ID_magnetometer_LEN;
        memset(magnetometer, 0, MAVLINK_MSG_ID_magnetometer_LEN);
    memcpy(magnetometer, _MAV_PAYLOAD(msg), len);
#endif
}
