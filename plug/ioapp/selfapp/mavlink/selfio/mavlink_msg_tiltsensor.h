#pragma once
// MESSAGE TiltSensor PACKING

#define MAVLINK_MSG_ID_TiltSensor 56109


typedef struct __mavlink_tiltsensor_t {
 double Tilt_X; /*<  TiltSensor_X*/
 double Tilt_Y; /*<  TiltSensor_Y*/
} mavlink_tiltsensor_t;

#define MAVLINK_MSG_ID_TiltSensor_LEN 16
#define MAVLINK_MSG_ID_TiltSensor_MIN_LEN 16
#define MAVLINK_MSG_ID_56109_LEN 16
#define MAVLINK_MSG_ID_56109_MIN_LEN 16

#define MAVLINK_MSG_ID_TiltSensor_CRC 98
#define MAVLINK_MSG_ID_56109_CRC 98



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TiltSensor { \
    56109, \
    "TiltSensor", \
    2, \
    {  { "Tilt_X", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_tiltsensor_t, Tilt_X) }, \
         { "Tilt_Y", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_tiltsensor_t, Tilt_Y) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TiltSensor { \
    "TiltSensor", \
    2, \
    {  { "Tilt_X", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_tiltsensor_t, Tilt_X) }, \
         { "Tilt_Y", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_tiltsensor_t, Tilt_Y) }, \
         } \
}
#endif

/**
 * @brief Pack a tiltsensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Tilt_X  TiltSensor_X
 * @param Tilt_Y  TiltSensor_Y
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tiltsensor_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double Tilt_X, double Tilt_Y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TiltSensor_LEN];
    _mav_put_double(buf, 0, Tilt_X);
    _mav_put_double(buf, 8, Tilt_Y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TiltSensor_LEN);
#else
    mavlink_tiltsensor_t packet;
    packet.Tilt_X = Tilt_X;
    packet.Tilt_Y = Tilt_Y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TiltSensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TiltSensor;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TiltSensor_MIN_LEN, MAVLINK_MSG_ID_TiltSensor_LEN, MAVLINK_MSG_ID_TiltSensor_CRC);
}

/**
 * @brief Pack a tiltsensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Tilt_X  TiltSensor_X
 * @param Tilt_Y  TiltSensor_Y
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tiltsensor_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double Tilt_X, double Tilt_Y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TiltSensor_LEN];
    _mav_put_double(buf, 0, Tilt_X);
    _mav_put_double(buf, 8, Tilt_Y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TiltSensor_LEN);
#else
    mavlink_tiltsensor_t packet;
    packet.Tilt_X = Tilt_X;
    packet.Tilt_Y = Tilt_Y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TiltSensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TiltSensor;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TiltSensor_MIN_LEN, MAVLINK_MSG_ID_TiltSensor_LEN, MAVLINK_MSG_ID_TiltSensor_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TiltSensor_MIN_LEN, MAVLINK_MSG_ID_TiltSensor_LEN);
#endif
}

/**
 * @brief Pack a tiltsensor message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Tilt_X  TiltSensor_X
 * @param Tilt_Y  TiltSensor_Y
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tiltsensor_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double Tilt_X,double Tilt_Y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TiltSensor_LEN];
    _mav_put_double(buf, 0, Tilt_X);
    _mav_put_double(buf, 8, Tilt_Y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TiltSensor_LEN);
#else
    mavlink_tiltsensor_t packet;
    packet.Tilt_X = Tilt_X;
    packet.Tilt_Y = Tilt_Y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TiltSensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TiltSensor;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TiltSensor_MIN_LEN, MAVLINK_MSG_ID_TiltSensor_LEN, MAVLINK_MSG_ID_TiltSensor_CRC);
}

/**
 * @brief Encode a tiltsensor struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tiltsensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tiltsensor_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tiltsensor_t* tiltsensor)
{
    return mavlink_msg_tiltsensor_pack(system_id, component_id, msg, tiltsensor->Tilt_X, tiltsensor->Tilt_Y);
}

/**
 * @brief Encode a tiltsensor struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tiltsensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tiltsensor_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tiltsensor_t* tiltsensor)
{
    return mavlink_msg_tiltsensor_pack_chan(system_id, component_id, chan, msg, tiltsensor->Tilt_X, tiltsensor->Tilt_Y);
}

/**
 * @brief Encode a tiltsensor struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param tiltsensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tiltsensor_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_tiltsensor_t* tiltsensor)
{
    return mavlink_msg_tiltsensor_pack_status(system_id, component_id, _status, msg,  tiltsensor->Tilt_X, tiltsensor->Tilt_Y);
}

/**
 * @brief Send a tiltsensor message
 * @param chan MAVLink channel to send the message
 *
 * @param Tilt_X  TiltSensor_X
 * @param Tilt_Y  TiltSensor_Y
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tiltsensor_send(mavlink_channel_t chan, double Tilt_X, double Tilt_Y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TiltSensor_LEN];
    _mav_put_double(buf, 0, Tilt_X);
    _mav_put_double(buf, 8, Tilt_Y);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TiltSensor, buf, MAVLINK_MSG_ID_TiltSensor_MIN_LEN, MAVLINK_MSG_ID_TiltSensor_LEN, MAVLINK_MSG_ID_TiltSensor_CRC);
#else
    mavlink_tiltsensor_t packet;
    packet.Tilt_X = Tilt_X;
    packet.Tilt_Y = Tilt_Y;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TiltSensor, (const char *)&packet, MAVLINK_MSG_ID_TiltSensor_MIN_LEN, MAVLINK_MSG_ID_TiltSensor_LEN, MAVLINK_MSG_ID_TiltSensor_CRC);
#endif
}

/**
 * @brief Send a tiltsensor message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tiltsensor_send_struct(mavlink_channel_t chan, const mavlink_tiltsensor_t* tiltsensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tiltsensor_send(chan, tiltsensor->Tilt_X, tiltsensor->Tilt_Y);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TiltSensor, (const char *)tiltsensor, MAVLINK_MSG_ID_TiltSensor_MIN_LEN, MAVLINK_MSG_ID_TiltSensor_LEN, MAVLINK_MSG_ID_TiltSensor_CRC);
#endif
}

#if MAVLINK_MSG_ID_TiltSensor_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tiltsensor_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double Tilt_X, double Tilt_Y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, Tilt_X);
    _mav_put_double(buf, 8, Tilt_Y);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TiltSensor, buf, MAVLINK_MSG_ID_TiltSensor_MIN_LEN, MAVLINK_MSG_ID_TiltSensor_LEN, MAVLINK_MSG_ID_TiltSensor_CRC);
#else
    mavlink_tiltsensor_t *packet = (mavlink_tiltsensor_t *)msgbuf;
    packet->Tilt_X = Tilt_X;
    packet->Tilt_Y = Tilt_Y;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TiltSensor, (const char *)packet, MAVLINK_MSG_ID_TiltSensor_MIN_LEN, MAVLINK_MSG_ID_TiltSensor_LEN, MAVLINK_MSG_ID_TiltSensor_CRC);
#endif
}
#endif

#endif

// MESSAGE TiltSensor UNPACKING


/**
 * @brief Get field Tilt_X from tiltsensor message
 *
 * @return  TiltSensor_X
 */
static inline double mavlink_msg_tiltsensor_get_Tilt_X(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Get field Tilt_Y from tiltsensor message
 *
 * @return  TiltSensor_Y
 */
static inline double mavlink_msg_tiltsensor_get_Tilt_Y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  8);
}

/**
 * @brief Decode a tiltsensor message into a struct
 *
 * @param msg The message to decode
 * @param tiltsensor C-struct to decode the message contents into
 */
static inline void mavlink_msg_tiltsensor_decode(const mavlink_message_t* msg, mavlink_tiltsensor_t* tiltsensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    tiltsensor->Tilt_X = mavlink_msg_tiltsensor_get_Tilt_X(msg);
    tiltsensor->Tilt_Y = mavlink_msg_tiltsensor_get_Tilt_Y(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TiltSensor_LEN? msg->len : MAVLINK_MSG_ID_TiltSensor_LEN;
        memset(tiltsensor, 0, MAVLINK_MSG_ID_TiltSensor_LEN);
    memcpy(tiltsensor, _MAV_PAYLOAD(msg), len);
#endif
}
