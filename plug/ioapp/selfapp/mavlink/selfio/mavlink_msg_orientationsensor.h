#pragma once
// MESSAGE OrientationSensor PACKING

#define MAVLINK_MSG_ID_OrientationSensor 56108


typedef struct __mavlink_orientationsensor_t {
 double Orientation; /*<  OrientationSensor*/
} mavlink_orientationsensor_t;

#define MAVLINK_MSG_ID_OrientationSensor_LEN 8
#define MAVLINK_MSG_ID_OrientationSensor_MIN_LEN 8
#define MAVLINK_MSG_ID_56108_LEN 8
#define MAVLINK_MSG_ID_56108_MIN_LEN 8

#define MAVLINK_MSG_ID_OrientationSensor_CRC 165
#define MAVLINK_MSG_ID_56108_CRC 165



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_OrientationSensor { \
    56108, \
    "OrientationSensor", \
    1, \
    {  { "Orientation", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_orientationsensor_t, Orientation) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_OrientationSensor { \
    "OrientationSensor", \
    1, \
    {  { "Orientation", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_orientationsensor_t, Orientation) }, \
         } \
}
#endif

/**
 * @brief Pack a orientationsensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Orientation  OrientationSensor
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_orientationsensor_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double Orientation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OrientationSensor_LEN];
    _mav_put_double(buf, 0, Orientation);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OrientationSensor_LEN);
#else
    mavlink_orientationsensor_t packet;
    packet.Orientation = Orientation;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OrientationSensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OrientationSensor;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_OrientationSensor_MIN_LEN, MAVLINK_MSG_ID_OrientationSensor_LEN, MAVLINK_MSG_ID_OrientationSensor_CRC);
}

/**
 * @brief Pack a orientationsensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Orientation  OrientationSensor
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_orientationsensor_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double Orientation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OrientationSensor_LEN];
    _mav_put_double(buf, 0, Orientation);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OrientationSensor_LEN);
#else
    mavlink_orientationsensor_t packet;
    packet.Orientation = Orientation;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OrientationSensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OrientationSensor;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_OrientationSensor_MIN_LEN, MAVLINK_MSG_ID_OrientationSensor_LEN, MAVLINK_MSG_ID_OrientationSensor_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_OrientationSensor_MIN_LEN, MAVLINK_MSG_ID_OrientationSensor_LEN);
#endif
}

/**
 * @brief Pack a orientationsensor message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Orientation  OrientationSensor
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_orientationsensor_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double Orientation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OrientationSensor_LEN];
    _mav_put_double(buf, 0, Orientation);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OrientationSensor_LEN);
#else
    mavlink_orientationsensor_t packet;
    packet.Orientation = Orientation;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OrientationSensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OrientationSensor;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_OrientationSensor_MIN_LEN, MAVLINK_MSG_ID_OrientationSensor_LEN, MAVLINK_MSG_ID_OrientationSensor_CRC);
}

/**
 * @brief Encode a orientationsensor struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param orientationsensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_orientationsensor_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_orientationsensor_t* orientationsensor)
{
    return mavlink_msg_orientationsensor_pack(system_id, component_id, msg, orientationsensor->Orientation);
}

/**
 * @brief Encode a orientationsensor struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param orientationsensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_orientationsensor_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_orientationsensor_t* orientationsensor)
{
    return mavlink_msg_orientationsensor_pack_chan(system_id, component_id, chan, msg, orientationsensor->Orientation);
}

/**
 * @brief Encode a orientationsensor struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param orientationsensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_orientationsensor_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_orientationsensor_t* orientationsensor)
{
    return mavlink_msg_orientationsensor_pack_status(system_id, component_id, _status, msg,  orientationsensor->Orientation);
}

/**
 * @brief Send a orientationsensor message
 * @param chan MAVLink channel to send the message
 *
 * @param Orientation  OrientationSensor
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_orientationsensor_send(mavlink_channel_t chan, double Orientation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OrientationSensor_LEN];
    _mav_put_double(buf, 0, Orientation);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OrientationSensor, buf, MAVLINK_MSG_ID_OrientationSensor_MIN_LEN, MAVLINK_MSG_ID_OrientationSensor_LEN, MAVLINK_MSG_ID_OrientationSensor_CRC);
#else
    mavlink_orientationsensor_t packet;
    packet.Orientation = Orientation;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OrientationSensor, (const char *)&packet, MAVLINK_MSG_ID_OrientationSensor_MIN_LEN, MAVLINK_MSG_ID_OrientationSensor_LEN, MAVLINK_MSG_ID_OrientationSensor_CRC);
#endif
}

/**
 * @brief Send a orientationsensor message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_orientationsensor_send_struct(mavlink_channel_t chan, const mavlink_orientationsensor_t* orientationsensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_orientationsensor_send(chan, orientationsensor->Orientation);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OrientationSensor, (const char *)orientationsensor, MAVLINK_MSG_ID_OrientationSensor_MIN_LEN, MAVLINK_MSG_ID_OrientationSensor_LEN, MAVLINK_MSG_ID_OrientationSensor_CRC);
#endif
}

#if MAVLINK_MSG_ID_OrientationSensor_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_orientationsensor_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double Orientation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, Orientation);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OrientationSensor, buf, MAVLINK_MSG_ID_OrientationSensor_MIN_LEN, MAVLINK_MSG_ID_OrientationSensor_LEN, MAVLINK_MSG_ID_OrientationSensor_CRC);
#else
    mavlink_orientationsensor_t *packet = (mavlink_orientationsensor_t *)msgbuf;
    packet->Orientation = Orientation;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OrientationSensor, (const char *)packet, MAVLINK_MSG_ID_OrientationSensor_MIN_LEN, MAVLINK_MSG_ID_OrientationSensor_LEN, MAVLINK_MSG_ID_OrientationSensor_CRC);
#endif
}
#endif

#endif

// MESSAGE OrientationSensor UNPACKING


/**
 * @brief Get field Orientation from orientationsensor message
 *
 * @return  OrientationSensor
 */
static inline double mavlink_msg_orientationsensor_get_Orientation(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Decode a orientationsensor message into a struct
 *
 * @param msg The message to decode
 * @param orientationsensor C-struct to decode the message contents into
 */
static inline void mavlink_msg_orientationsensor_decode(const mavlink_message_t* msg, mavlink_orientationsensor_t* orientationsensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    orientationsensor->Orientation = mavlink_msg_orientationsensor_get_Orientation(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_OrientationSensor_LEN? msg->len : MAVLINK_MSG_ID_OrientationSensor_LEN;
        memset(orientationsensor, 0, MAVLINK_MSG_ID_OrientationSensor_LEN);
    memcpy(orientationsensor, _MAV_PAYLOAD(msg), len);
#endif
}
