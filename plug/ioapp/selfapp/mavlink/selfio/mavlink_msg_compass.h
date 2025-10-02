#pragma once
// MESSAGE compass PACKING

#define MAVLINK_MSG_ID_compass 56103


typedef struct __mavlink_compass_t {
 double Compass; /*<  Compass*/
} mavlink_compass_t;

#define MAVLINK_MSG_ID_compass_LEN 8
#define MAVLINK_MSG_ID_compass_MIN_LEN 8
#define MAVLINK_MSG_ID_56103_LEN 8
#define MAVLINK_MSG_ID_56103_MIN_LEN 8

#define MAVLINK_MSG_ID_compass_CRC 38
#define MAVLINK_MSG_ID_56103_CRC 38



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_compass { \
    56103, \
    "compass", \
    1, \
    {  { "Compass", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_compass_t, Compass) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_compass { \
    "compass", \
    1, \
    {  { "Compass", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_compass_t, Compass) }, \
         } \
}
#endif

/**
 * @brief Pack a compass message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Compass  Compass
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_compass_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double Compass)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_compass_LEN];
    _mav_put_double(buf, 0, Compass);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_compass_LEN);
#else
    mavlink_compass_t packet;
    packet.Compass = Compass;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_compass_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_compass;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_compass_MIN_LEN, MAVLINK_MSG_ID_compass_LEN, MAVLINK_MSG_ID_compass_CRC);
}

/**
 * @brief Pack a compass message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Compass  Compass
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_compass_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double Compass)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_compass_LEN];
    _mav_put_double(buf, 0, Compass);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_compass_LEN);
#else
    mavlink_compass_t packet;
    packet.Compass = Compass;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_compass_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_compass;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_compass_MIN_LEN, MAVLINK_MSG_ID_compass_LEN, MAVLINK_MSG_ID_compass_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_compass_MIN_LEN, MAVLINK_MSG_ID_compass_LEN);
#endif
}

/**
 * @brief Pack a compass message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Compass  Compass
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_compass_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double Compass)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_compass_LEN];
    _mav_put_double(buf, 0, Compass);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_compass_LEN);
#else
    mavlink_compass_t packet;
    packet.Compass = Compass;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_compass_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_compass;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_compass_MIN_LEN, MAVLINK_MSG_ID_compass_LEN, MAVLINK_MSG_ID_compass_CRC);
}

/**
 * @brief Encode a compass struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param compass C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_compass_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_compass_t* compass)
{
    return mavlink_msg_compass_pack(system_id, component_id, msg, compass->Compass);
}

/**
 * @brief Encode a compass struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param compass C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_compass_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_compass_t* compass)
{
    return mavlink_msg_compass_pack_chan(system_id, component_id, chan, msg, compass->Compass);
}

/**
 * @brief Encode a compass struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param compass C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_compass_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_compass_t* compass)
{
    return mavlink_msg_compass_pack_status(system_id, component_id, _status, msg,  compass->Compass);
}

/**
 * @brief Send a compass message
 * @param chan MAVLink channel to send the message
 *
 * @param Compass  Compass
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_compass_send(mavlink_channel_t chan, double Compass)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_compass_LEN];
    _mav_put_double(buf, 0, Compass);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_compass, buf, MAVLINK_MSG_ID_compass_MIN_LEN, MAVLINK_MSG_ID_compass_LEN, MAVLINK_MSG_ID_compass_CRC);
#else
    mavlink_compass_t packet;
    packet.Compass = Compass;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_compass, (const char *)&packet, MAVLINK_MSG_ID_compass_MIN_LEN, MAVLINK_MSG_ID_compass_LEN, MAVLINK_MSG_ID_compass_CRC);
#endif
}

/**
 * @brief Send a compass message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_compass_send_struct(mavlink_channel_t chan, const mavlink_compass_t* compass)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_compass_send(chan, compass->Compass);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_compass, (const char *)compass, MAVLINK_MSG_ID_compass_MIN_LEN, MAVLINK_MSG_ID_compass_LEN, MAVLINK_MSG_ID_compass_CRC);
#endif
}

#if MAVLINK_MSG_ID_compass_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_compass_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double Compass)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, Compass);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_compass, buf, MAVLINK_MSG_ID_compass_MIN_LEN, MAVLINK_MSG_ID_compass_LEN, MAVLINK_MSG_ID_compass_CRC);
#else
    mavlink_compass_t *packet = (mavlink_compass_t *)msgbuf;
    packet->Compass = Compass;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_compass, (const char *)packet, MAVLINK_MSG_ID_compass_MIN_LEN, MAVLINK_MSG_ID_compass_LEN, MAVLINK_MSG_ID_compass_CRC);
#endif
}
#endif

#endif

// MESSAGE compass UNPACKING


/**
 * @brief Get field Compass from compass message
 *
 * @return  Compass
 */
static inline double mavlink_msg_compass_get_Compass(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Decode a compass message into a struct
 *
 * @param msg The message to decode
 * @param compass C-struct to decode the message contents into
 */
static inline void mavlink_msg_compass_decode(const mavlink_message_t* msg, mavlink_compass_t* compass)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    compass->Compass = mavlink_msg_compass_get_Compass(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_compass_LEN? msg->len : MAVLINK_MSG_ID_compass_LEN;
        memset(compass, 0, MAVLINK_MSG_ID_compass_LEN);
    memcpy(compass, _MAV_PAYLOAD(msg), len);
#endif
}
