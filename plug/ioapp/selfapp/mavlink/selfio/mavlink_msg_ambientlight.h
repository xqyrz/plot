#pragma once
// MESSAGE ambientLight PACKING

#define MAVLINK_MSG_ID_ambientLight 56106


typedef struct __mavlink_ambientlight_t {
 double ambientLight; /*<  ambientLight*/
} mavlink_ambientlight_t;

#define MAVLINK_MSG_ID_ambientLight_LEN 8
#define MAVLINK_MSG_ID_ambientLight_MIN_LEN 8
#define MAVLINK_MSG_ID_56106_LEN 8
#define MAVLINK_MSG_ID_56106_MIN_LEN 8

#define MAVLINK_MSG_ID_ambientLight_CRC 232
#define MAVLINK_MSG_ID_56106_CRC 232



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ambientLight { \
    56106, \
    "ambientLight", \
    1, \
    {  { "ambientLight", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_ambientlight_t, ambientLight) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ambientLight { \
    "ambientLight", \
    1, \
    {  { "ambientLight", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_ambientlight_t, ambientLight) }, \
         } \
}
#endif

/**
 * @brief Pack a ambientlight message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param ambientLight  ambientLight
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ambientlight_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double ambientLight)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ambientLight_LEN];
    _mav_put_double(buf, 0, ambientLight);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ambientLight_LEN);
#else
    mavlink_ambientlight_t packet;
    packet.ambientLight = ambientLight;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ambientLight_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ambientLight;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ambientLight_MIN_LEN, MAVLINK_MSG_ID_ambientLight_LEN, MAVLINK_MSG_ID_ambientLight_CRC);
}

/**
 * @brief Pack a ambientlight message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param ambientLight  ambientLight
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ambientlight_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double ambientLight)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ambientLight_LEN];
    _mav_put_double(buf, 0, ambientLight);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ambientLight_LEN);
#else
    mavlink_ambientlight_t packet;
    packet.ambientLight = ambientLight;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ambientLight_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ambientLight;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ambientLight_MIN_LEN, MAVLINK_MSG_ID_ambientLight_LEN, MAVLINK_MSG_ID_ambientLight_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ambientLight_MIN_LEN, MAVLINK_MSG_ID_ambientLight_LEN);
#endif
}

/**
 * @brief Pack a ambientlight message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ambientLight  ambientLight
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ambientlight_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double ambientLight)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ambientLight_LEN];
    _mav_put_double(buf, 0, ambientLight);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ambientLight_LEN);
#else
    mavlink_ambientlight_t packet;
    packet.ambientLight = ambientLight;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ambientLight_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ambientLight;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ambientLight_MIN_LEN, MAVLINK_MSG_ID_ambientLight_LEN, MAVLINK_MSG_ID_ambientLight_CRC);
}

/**
 * @brief Encode a ambientlight struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param ambientlight C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ambientlight_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_ambientlight_t* ambientlight)
{
    return mavlink_msg_ambientlight_pack(system_id, component_id, msg, ambientlight->ambientLight);
}

/**
 * @brief Encode a ambientlight struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ambientlight C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ambientlight_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_ambientlight_t* ambientlight)
{
    return mavlink_msg_ambientlight_pack_chan(system_id, component_id, chan, msg, ambientlight->ambientLight);
}

/**
 * @brief Encode a ambientlight struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param ambientlight C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ambientlight_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_ambientlight_t* ambientlight)
{
    return mavlink_msg_ambientlight_pack_status(system_id, component_id, _status, msg,  ambientlight->ambientLight);
}

/**
 * @brief Send a ambientlight message
 * @param chan MAVLink channel to send the message
 *
 * @param ambientLight  ambientLight
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_ambientlight_send(mavlink_channel_t chan, double ambientLight)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ambientLight_LEN];
    _mav_put_double(buf, 0, ambientLight);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ambientLight, buf, MAVLINK_MSG_ID_ambientLight_MIN_LEN, MAVLINK_MSG_ID_ambientLight_LEN, MAVLINK_MSG_ID_ambientLight_CRC);
#else
    mavlink_ambientlight_t packet;
    packet.ambientLight = ambientLight;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ambientLight, (const char *)&packet, MAVLINK_MSG_ID_ambientLight_MIN_LEN, MAVLINK_MSG_ID_ambientLight_LEN, MAVLINK_MSG_ID_ambientLight_CRC);
#endif
}

/**
 * @brief Send a ambientlight message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_ambientlight_send_struct(mavlink_channel_t chan, const mavlink_ambientlight_t* ambientlight)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_ambientlight_send(chan, ambientlight->ambientLight);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ambientLight, (const char *)ambientlight, MAVLINK_MSG_ID_ambientLight_MIN_LEN, MAVLINK_MSG_ID_ambientLight_LEN, MAVLINK_MSG_ID_ambientLight_CRC);
#endif
}

#if MAVLINK_MSG_ID_ambientLight_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_ambientlight_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double ambientLight)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, ambientLight);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ambientLight, buf, MAVLINK_MSG_ID_ambientLight_MIN_LEN, MAVLINK_MSG_ID_ambientLight_LEN, MAVLINK_MSG_ID_ambientLight_CRC);
#else
    mavlink_ambientlight_t *packet = (mavlink_ambientlight_t *)msgbuf;
    packet->ambientLight = ambientLight;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ambientLight, (const char *)packet, MAVLINK_MSG_ID_ambientLight_MIN_LEN, MAVLINK_MSG_ID_ambientLight_LEN, MAVLINK_MSG_ID_ambientLight_CRC);
#endif
}
#endif

#endif

// MESSAGE ambientLight UNPACKING


/**
 * @brief Get field ambientLight from ambientlight message
 *
 * @return  ambientLight
 */
static inline double mavlink_msg_ambientlight_get_ambientLight(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Decode a ambientlight message into a struct
 *
 * @param msg The message to decode
 * @param ambientlight C-struct to decode the message contents into
 */
static inline void mavlink_msg_ambientlight_decode(const mavlink_message_t* msg, mavlink_ambientlight_t* ambientlight)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    ambientlight->ambientLight = mavlink_msg_ambientlight_get_ambientLight(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ambientLight_LEN? msg->len : MAVLINK_MSG_ID_ambientLight_LEN;
        memset(ambientlight, 0, MAVLINK_MSG_ID_ambientLight_LEN);
    memcpy(ambientlight, _MAV_PAYLOAD(msg), len);
#endif
}
