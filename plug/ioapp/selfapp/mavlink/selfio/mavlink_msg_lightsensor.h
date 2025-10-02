#pragma once
// MESSAGE lightSensor PACKING

#define MAVLINK_MSG_ID_lightSensor 56105


typedef struct __mavlink_lightsensor_t {
 double light; /*<  light*/
} mavlink_lightsensor_t;

#define MAVLINK_MSG_ID_lightSensor_LEN 8
#define MAVLINK_MSG_ID_lightSensor_MIN_LEN 8
#define MAVLINK_MSG_ID_56105_LEN 8
#define MAVLINK_MSG_ID_56105_MIN_LEN 8

#define MAVLINK_MSG_ID_lightSensor_CRC 53
#define MAVLINK_MSG_ID_56105_CRC 53



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_lightSensor { \
    56105, \
    "lightSensor", \
    1, \
    {  { "light", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_lightsensor_t, light) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_lightSensor { \
    "lightSensor", \
    1, \
    {  { "light", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_lightsensor_t, light) }, \
         } \
}
#endif

/**
 * @brief Pack a lightsensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param light  light
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lightsensor_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_lightSensor_LEN];
    _mav_put_double(buf, 0, light);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_lightSensor_LEN);
#else
    mavlink_lightsensor_t packet;
    packet.light = light;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_lightSensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_lightSensor;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_lightSensor_MIN_LEN, MAVLINK_MSG_ID_lightSensor_LEN, MAVLINK_MSG_ID_lightSensor_CRC);
}

/**
 * @brief Pack a lightsensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param light  light
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lightsensor_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_lightSensor_LEN];
    _mav_put_double(buf, 0, light);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_lightSensor_LEN);
#else
    mavlink_lightsensor_t packet;
    packet.light = light;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_lightSensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_lightSensor;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_lightSensor_MIN_LEN, MAVLINK_MSG_ID_lightSensor_LEN, MAVLINK_MSG_ID_lightSensor_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_lightSensor_MIN_LEN, MAVLINK_MSG_ID_lightSensor_LEN);
#endif
}

/**
 * @brief Pack a lightsensor message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param light  light
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lightsensor_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_lightSensor_LEN];
    _mav_put_double(buf, 0, light);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_lightSensor_LEN);
#else
    mavlink_lightsensor_t packet;
    packet.light = light;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_lightSensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_lightSensor;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_lightSensor_MIN_LEN, MAVLINK_MSG_ID_lightSensor_LEN, MAVLINK_MSG_ID_lightSensor_CRC);
}

/**
 * @brief Encode a lightsensor struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param lightsensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lightsensor_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_lightsensor_t* lightsensor)
{
    return mavlink_msg_lightsensor_pack(system_id, component_id, msg, lightsensor->light);
}

/**
 * @brief Encode a lightsensor struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lightsensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lightsensor_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_lightsensor_t* lightsensor)
{
    return mavlink_msg_lightsensor_pack_chan(system_id, component_id, chan, msg, lightsensor->light);
}

/**
 * @brief Encode a lightsensor struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param lightsensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lightsensor_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_lightsensor_t* lightsensor)
{
    return mavlink_msg_lightsensor_pack_status(system_id, component_id, _status, msg,  lightsensor->light);
}

/**
 * @brief Send a lightsensor message
 * @param chan MAVLink channel to send the message
 *
 * @param light  light
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_lightsensor_send(mavlink_channel_t chan, double light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_lightSensor_LEN];
    _mav_put_double(buf, 0, light);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_lightSensor, buf, MAVLINK_MSG_ID_lightSensor_MIN_LEN, MAVLINK_MSG_ID_lightSensor_LEN, MAVLINK_MSG_ID_lightSensor_CRC);
#else
    mavlink_lightsensor_t packet;
    packet.light = light;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_lightSensor, (const char *)&packet, MAVLINK_MSG_ID_lightSensor_MIN_LEN, MAVLINK_MSG_ID_lightSensor_LEN, MAVLINK_MSG_ID_lightSensor_CRC);
#endif
}

/**
 * @brief Send a lightsensor message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_lightsensor_send_struct(mavlink_channel_t chan, const mavlink_lightsensor_t* lightsensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_lightsensor_send(chan, lightsensor->light);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_lightSensor, (const char *)lightsensor, MAVLINK_MSG_ID_lightSensor_MIN_LEN, MAVLINK_MSG_ID_lightSensor_LEN, MAVLINK_MSG_ID_lightSensor_CRC);
#endif
}

#if MAVLINK_MSG_ID_lightSensor_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_lightsensor_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, light);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_lightSensor, buf, MAVLINK_MSG_ID_lightSensor_MIN_LEN, MAVLINK_MSG_ID_lightSensor_LEN, MAVLINK_MSG_ID_lightSensor_CRC);
#else
    mavlink_lightsensor_t *packet = (mavlink_lightsensor_t *)msgbuf;
    packet->light = light;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_lightSensor, (const char *)packet, MAVLINK_MSG_ID_lightSensor_MIN_LEN, MAVLINK_MSG_ID_lightSensor_LEN, MAVLINK_MSG_ID_lightSensor_CRC);
#endif
}
#endif

#endif

// MESSAGE lightSensor UNPACKING


/**
 * @brief Get field light from lightsensor message
 *
 * @return  light
 */
static inline double mavlink_msg_lightsensor_get_light(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Decode a lightsensor message into a struct
 *
 * @param msg The message to decode
 * @param lightsensor C-struct to decode the message contents into
 */
static inline void mavlink_msg_lightsensor_decode(const mavlink_message_t* msg, mavlink_lightsensor_t* lightsensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    lightsensor->light = mavlink_msg_lightsensor_get_light(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_lightSensor_LEN? msg->len : MAVLINK_MSG_ID_lightSensor_LEN;
        memset(lightsensor, 0, MAVLINK_MSG_ID_lightSensor_LEN);
    memcpy(lightsensor, _MAV_PAYLOAD(msg), len);
#endif
}
