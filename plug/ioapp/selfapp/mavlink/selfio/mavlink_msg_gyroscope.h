#pragma once
// MESSAGE gyroscope PACKING

#define MAVLINK_MSG_ID_gyroscope 56101


typedef struct __mavlink_gyroscope_t {
 double GYRO_X; /*<  GYRO_X*/
 double GYRO_Y; /*<  GYRO_Y*/
 double GYRO_Z; /*<  GYRO_Z*/
} mavlink_gyroscope_t;

#define MAVLINK_MSG_ID_gyroscope_LEN 24
#define MAVLINK_MSG_ID_gyroscope_MIN_LEN 24
#define MAVLINK_MSG_ID_56101_LEN 24
#define MAVLINK_MSG_ID_56101_MIN_LEN 24

#define MAVLINK_MSG_ID_gyroscope_CRC 193
#define MAVLINK_MSG_ID_56101_CRC 193



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_gyroscope { \
    56101, \
    "gyroscope", \
    3, \
    {  { "GYRO_X", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_gyroscope_t, GYRO_X) }, \
         { "GYRO_Y", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_gyroscope_t, GYRO_Y) }, \
         { "GYRO_Z", NULL, MAVLINK_TYPE_DOUBLE, 0, 16, offsetof(mavlink_gyroscope_t, GYRO_Z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_gyroscope { \
    "gyroscope", \
    3, \
    {  { "GYRO_X", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_gyroscope_t, GYRO_X) }, \
         { "GYRO_Y", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_gyroscope_t, GYRO_Y) }, \
         { "GYRO_Z", NULL, MAVLINK_TYPE_DOUBLE, 0, 16, offsetof(mavlink_gyroscope_t, GYRO_Z) }, \
         } \
}
#endif

/**
 * @brief Pack a gyroscope message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param GYRO_X  GYRO_X
 * @param GYRO_Y  GYRO_Y
 * @param GYRO_Z  GYRO_Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gyroscope_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double GYRO_X, double GYRO_Y, double GYRO_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gyroscope_LEN];
    _mav_put_double(buf, 0, GYRO_X);
    _mav_put_double(buf, 8, GYRO_Y);
    _mav_put_double(buf, 16, GYRO_Z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_gyroscope_LEN);
#else
    mavlink_gyroscope_t packet;
    packet.GYRO_X = GYRO_X;
    packet.GYRO_Y = GYRO_Y;
    packet.GYRO_Z = GYRO_Z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_gyroscope_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_gyroscope;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_gyroscope_MIN_LEN, MAVLINK_MSG_ID_gyroscope_LEN, MAVLINK_MSG_ID_gyroscope_CRC);
}

/**
 * @brief Pack a gyroscope message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param GYRO_X  GYRO_X
 * @param GYRO_Y  GYRO_Y
 * @param GYRO_Z  GYRO_Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gyroscope_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double GYRO_X, double GYRO_Y, double GYRO_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gyroscope_LEN];
    _mav_put_double(buf, 0, GYRO_X);
    _mav_put_double(buf, 8, GYRO_Y);
    _mav_put_double(buf, 16, GYRO_Z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_gyroscope_LEN);
#else
    mavlink_gyroscope_t packet;
    packet.GYRO_X = GYRO_X;
    packet.GYRO_Y = GYRO_Y;
    packet.GYRO_Z = GYRO_Z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_gyroscope_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_gyroscope;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_gyroscope_MIN_LEN, MAVLINK_MSG_ID_gyroscope_LEN, MAVLINK_MSG_ID_gyroscope_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_gyroscope_MIN_LEN, MAVLINK_MSG_ID_gyroscope_LEN);
#endif
}

/**
 * @brief Pack a gyroscope message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param GYRO_X  GYRO_X
 * @param GYRO_Y  GYRO_Y
 * @param GYRO_Z  GYRO_Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gyroscope_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double GYRO_X,double GYRO_Y,double GYRO_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gyroscope_LEN];
    _mav_put_double(buf, 0, GYRO_X);
    _mav_put_double(buf, 8, GYRO_Y);
    _mav_put_double(buf, 16, GYRO_Z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_gyroscope_LEN);
#else
    mavlink_gyroscope_t packet;
    packet.GYRO_X = GYRO_X;
    packet.GYRO_Y = GYRO_Y;
    packet.GYRO_Z = GYRO_Z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_gyroscope_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_gyroscope;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_gyroscope_MIN_LEN, MAVLINK_MSG_ID_gyroscope_LEN, MAVLINK_MSG_ID_gyroscope_CRC);
}

/**
 * @brief Encode a gyroscope struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gyroscope C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gyroscope_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gyroscope_t* gyroscope)
{
    return mavlink_msg_gyroscope_pack(system_id, component_id, msg, gyroscope->GYRO_X, gyroscope->GYRO_Y, gyroscope->GYRO_Z);
}

/**
 * @brief Encode a gyroscope struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gyroscope C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gyroscope_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gyroscope_t* gyroscope)
{
    return mavlink_msg_gyroscope_pack_chan(system_id, component_id, chan, msg, gyroscope->GYRO_X, gyroscope->GYRO_Y, gyroscope->GYRO_Z);
}

/**
 * @brief Encode a gyroscope struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param gyroscope C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gyroscope_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_gyroscope_t* gyroscope)
{
    return mavlink_msg_gyroscope_pack_status(system_id, component_id, _status, msg,  gyroscope->GYRO_X, gyroscope->GYRO_Y, gyroscope->GYRO_Z);
}

/**
 * @brief Send a gyroscope message
 * @param chan MAVLink channel to send the message
 *
 * @param GYRO_X  GYRO_X
 * @param GYRO_Y  GYRO_Y
 * @param GYRO_Z  GYRO_Z
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gyroscope_send(mavlink_channel_t chan, double GYRO_X, double GYRO_Y, double GYRO_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_gyroscope_LEN];
    _mav_put_double(buf, 0, GYRO_X);
    _mav_put_double(buf, 8, GYRO_Y);
    _mav_put_double(buf, 16, GYRO_Z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyroscope, buf, MAVLINK_MSG_ID_gyroscope_MIN_LEN, MAVLINK_MSG_ID_gyroscope_LEN, MAVLINK_MSG_ID_gyroscope_CRC);
#else
    mavlink_gyroscope_t packet;
    packet.GYRO_X = GYRO_X;
    packet.GYRO_Y = GYRO_Y;
    packet.GYRO_Z = GYRO_Z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyroscope, (const char *)&packet, MAVLINK_MSG_ID_gyroscope_MIN_LEN, MAVLINK_MSG_ID_gyroscope_LEN, MAVLINK_MSG_ID_gyroscope_CRC);
#endif
}

/**
 * @brief Send a gyroscope message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gyroscope_send_struct(mavlink_channel_t chan, const mavlink_gyroscope_t* gyroscope)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gyroscope_send(chan, gyroscope->GYRO_X, gyroscope->GYRO_Y, gyroscope->GYRO_Z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyroscope, (const char *)gyroscope, MAVLINK_MSG_ID_gyroscope_MIN_LEN, MAVLINK_MSG_ID_gyroscope_LEN, MAVLINK_MSG_ID_gyroscope_CRC);
#endif
}

#if MAVLINK_MSG_ID_gyroscope_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gyroscope_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double GYRO_X, double GYRO_Y, double GYRO_Z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, GYRO_X);
    _mav_put_double(buf, 8, GYRO_Y);
    _mav_put_double(buf, 16, GYRO_Z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyroscope, buf, MAVLINK_MSG_ID_gyroscope_MIN_LEN, MAVLINK_MSG_ID_gyroscope_LEN, MAVLINK_MSG_ID_gyroscope_CRC);
#else
    mavlink_gyroscope_t *packet = (mavlink_gyroscope_t *)msgbuf;
    packet->GYRO_X = GYRO_X;
    packet->GYRO_Y = GYRO_Y;
    packet->GYRO_Z = GYRO_Z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_gyroscope, (const char *)packet, MAVLINK_MSG_ID_gyroscope_MIN_LEN, MAVLINK_MSG_ID_gyroscope_LEN, MAVLINK_MSG_ID_gyroscope_CRC);
#endif
}
#endif

#endif

// MESSAGE gyroscope UNPACKING


/**
 * @brief Get field GYRO_X from gyroscope message
 *
 * @return  GYRO_X
 */
static inline double mavlink_msg_gyroscope_get_GYRO_X(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Get field GYRO_Y from gyroscope message
 *
 * @return  GYRO_Y
 */
static inline double mavlink_msg_gyroscope_get_GYRO_Y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  8);
}

/**
 * @brief Get field GYRO_Z from gyroscope message
 *
 * @return  GYRO_Z
 */
static inline double mavlink_msg_gyroscope_get_GYRO_Z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  16);
}

/**
 * @brief Decode a gyroscope message into a struct
 *
 * @param msg The message to decode
 * @param gyroscope C-struct to decode the message contents into
 */
static inline void mavlink_msg_gyroscope_decode(const mavlink_message_t* msg, mavlink_gyroscope_t* gyroscope)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    gyroscope->GYRO_X = mavlink_msg_gyroscope_get_GYRO_X(msg);
    gyroscope->GYRO_Y = mavlink_msg_gyroscope_get_GYRO_Y(msg);
    gyroscope->GYRO_Z = mavlink_msg_gyroscope_get_GYRO_Z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_gyroscope_LEN? msg->len : MAVLINK_MSG_ID_gyroscope_LEN;
        memset(gyroscope, 0, MAVLINK_MSG_ID_gyroscope_LEN);
    memcpy(gyroscope, _MAV_PAYLOAD(msg), len);
#endif
}
