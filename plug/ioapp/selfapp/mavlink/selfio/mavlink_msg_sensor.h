#pragma once
// MESSAGE sensor PACKING

#define MAVLINK_MSG_ID_sensor 56000


typedef struct __mavlink_sensor_t {
 double sensor1; /*<  sensor1 value*/
} mavlink_sensor_t;

#define MAVLINK_MSG_ID_sensor_LEN 8
#define MAVLINK_MSG_ID_sensor_MIN_LEN 8
#define MAVLINK_MSG_ID_56000_LEN 8
#define MAVLINK_MSG_ID_56000_MIN_LEN 8

#define MAVLINK_MSG_ID_sensor_CRC 25
#define MAVLINK_MSG_ID_56000_CRC 25



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_sensor { \
    56000, \
    "sensor", \
    1, \
    {  { "sensor1", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_sensor_t, sensor1) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_sensor { \
    "sensor", \
    1, \
    {  { "sensor1", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_sensor_t, sensor1) }, \
         } \
}
#endif

/**
 * @brief Pack a sensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param sensor1  sensor1 value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double sensor1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_sensor_LEN];
    _mav_put_double(buf, 0, sensor1);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_sensor_LEN);
#else
    mavlink_sensor_t packet;
    packet.sensor1 = sensor1;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_sensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_sensor;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_sensor_MIN_LEN, MAVLINK_MSG_ID_sensor_LEN, MAVLINK_MSG_ID_sensor_CRC);
}

/**
 * @brief Pack a sensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param sensor1  sensor1 value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double sensor1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_sensor_LEN];
    _mav_put_double(buf, 0, sensor1);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_sensor_LEN);
#else
    mavlink_sensor_t packet;
    packet.sensor1 = sensor1;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_sensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_sensor;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_sensor_MIN_LEN, MAVLINK_MSG_ID_sensor_LEN, MAVLINK_MSG_ID_sensor_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_sensor_MIN_LEN, MAVLINK_MSG_ID_sensor_LEN);
#endif
}

/**
 * @brief Pack a sensor message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param sensor1  sensor1 value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double sensor1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_sensor_LEN];
    _mav_put_double(buf, 0, sensor1);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_sensor_LEN);
#else
    mavlink_sensor_t packet;
    packet.sensor1 = sensor1;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_sensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_sensor;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_sensor_MIN_LEN, MAVLINK_MSG_ID_sensor_LEN, MAVLINK_MSG_ID_sensor_CRC);
}

/**
 * @brief Encode a sensor struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param sensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_sensor_t* sensor)
{
    return mavlink_msg_sensor_pack(system_id, component_id, msg, sensor->sensor1);
}

/**
 * @brief Encode a sensor struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param sensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_sensor_t* sensor)
{
    return mavlink_msg_sensor_pack_chan(system_id, component_id, chan, msg, sensor->sensor1);
}

/**
 * @brief Encode a sensor struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param sensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_sensor_t* sensor)
{
    return mavlink_msg_sensor_pack_status(system_id, component_id, _status, msg,  sensor->sensor1);
}

/**
 * @brief Send a sensor message
 * @param chan MAVLink channel to send the message
 *
 * @param sensor1  sensor1 value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_sensor_send(mavlink_channel_t chan, double sensor1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_sensor_LEN];
    _mav_put_double(buf, 0, sensor1);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_sensor, buf, MAVLINK_MSG_ID_sensor_MIN_LEN, MAVLINK_MSG_ID_sensor_LEN, MAVLINK_MSG_ID_sensor_CRC);
#else
    mavlink_sensor_t packet;
    packet.sensor1 = sensor1;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_sensor, (const char *)&packet, MAVLINK_MSG_ID_sensor_MIN_LEN, MAVLINK_MSG_ID_sensor_LEN, MAVLINK_MSG_ID_sensor_CRC);
#endif
}

/**
 * @brief Send a sensor message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_sensor_send_struct(mavlink_channel_t chan, const mavlink_sensor_t* sensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_sensor_send(chan, sensor->sensor1);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_sensor, (const char *)sensor, MAVLINK_MSG_ID_sensor_MIN_LEN, MAVLINK_MSG_ID_sensor_LEN, MAVLINK_MSG_ID_sensor_CRC);
#endif
}

#if MAVLINK_MSG_ID_sensor_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_sensor_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double sensor1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, sensor1);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_sensor, buf, MAVLINK_MSG_ID_sensor_MIN_LEN, MAVLINK_MSG_ID_sensor_LEN, MAVLINK_MSG_ID_sensor_CRC);
#else
    mavlink_sensor_t *packet = (mavlink_sensor_t *)msgbuf;
    packet->sensor1 = sensor1;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_sensor, (const char *)packet, MAVLINK_MSG_ID_sensor_MIN_LEN, MAVLINK_MSG_ID_sensor_LEN, MAVLINK_MSG_ID_sensor_CRC);
#endif
}
#endif

#endif

// MESSAGE sensor UNPACKING


/**
 * @brief Get field sensor1 from sensor message
 *
 * @return  sensor1 value
 */
static inline double mavlink_msg_sensor_get_sensor1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Decode a sensor message into a struct
 *
 * @param msg The message to decode
 * @param sensor C-struct to decode the message contents into
 */
static inline void mavlink_msg_sensor_decode(const mavlink_message_t* msg, mavlink_sensor_t* sensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    sensor->sensor1 = mavlink_msg_sensor_get_sensor1(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_sensor_LEN? msg->len : MAVLINK_MSG_ID_sensor_LEN;
        memset(sensor, 0, MAVLINK_MSG_ID_sensor_LEN);
    memcpy(sensor, _MAV_PAYLOAD(msg), len);
#endif
}
