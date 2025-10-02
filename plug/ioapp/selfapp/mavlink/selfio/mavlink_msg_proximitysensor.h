#pragma once
// MESSAGE ProximitySensor PACKING

#define MAVLINK_MSG_ID_ProximitySensor 56107


typedef struct __mavlink_proximitysensor_t {
 double Proximity; /*<  ProximitySensor*/
} mavlink_proximitysensor_t;

#define MAVLINK_MSG_ID_ProximitySensor_LEN 8
#define MAVLINK_MSG_ID_ProximitySensor_MIN_LEN 8
#define MAVLINK_MSG_ID_56107_LEN 8
#define MAVLINK_MSG_ID_56107_MIN_LEN 8

#define MAVLINK_MSG_ID_ProximitySensor_CRC 250
#define MAVLINK_MSG_ID_56107_CRC 250



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ProximitySensor { \
    56107, \
    "ProximitySensor", \
    1, \
    {  { "Proximity", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_proximitysensor_t, Proximity) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ProximitySensor { \
    "ProximitySensor", \
    1, \
    {  { "Proximity", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_proximitysensor_t, Proximity) }, \
         } \
}
#endif

/**
 * @brief Pack a proximitysensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Proximity  ProximitySensor
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_proximitysensor_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double Proximity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ProximitySensor_LEN];
    _mav_put_double(buf, 0, Proximity);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ProximitySensor_LEN);
#else
    mavlink_proximitysensor_t packet;
    packet.Proximity = Proximity;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ProximitySensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ProximitySensor;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ProximitySensor_MIN_LEN, MAVLINK_MSG_ID_ProximitySensor_LEN, MAVLINK_MSG_ID_ProximitySensor_CRC);
}

/**
 * @brief Pack a proximitysensor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Proximity  ProximitySensor
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_proximitysensor_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double Proximity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ProximitySensor_LEN];
    _mav_put_double(buf, 0, Proximity);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ProximitySensor_LEN);
#else
    mavlink_proximitysensor_t packet;
    packet.Proximity = Proximity;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ProximitySensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ProximitySensor;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ProximitySensor_MIN_LEN, MAVLINK_MSG_ID_ProximitySensor_LEN, MAVLINK_MSG_ID_ProximitySensor_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ProximitySensor_MIN_LEN, MAVLINK_MSG_ID_ProximitySensor_LEN);
#endif
}

/**
 * @brief Pack a proximitysensor message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Proximity  ProximitySensor
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_proximitysensor_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double Proximity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ProximitySensor_LEN];
    _mav_put_double(buf, 0, Proximity);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ProximitySensor_LEN);
#else
    mavlink_proximitysensor_t packet;
    packet.Proximity = Proximity;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ProximitySensor_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ProximitySensor;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ProximitySensor_MIN_LEN, MAVLINK_MSG_ID_ProximitySensor_LEN, MAVLINK_MSG_ID_ProximitySensor_CRC);
}

/**
 * @brief Encode a proximitysensor struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param proximitysensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_proximitysensor_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_proximitysensor_t* proximitysensor)
{
    return mavlink_msg_proximitysensor_pack(system_id, component_id, msg, proximitysensor->Proximity);
}

/**
 * @brief Encode a proximitysensor struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param proximitysensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_proximitysensor_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_proximitysensor_t* proximitysensor)
{
    return mavlink_msg_proximitysensor_pack_chan(system_id, component_id, chan, msg, proximitysensor->Proximity);
}

/**
 * @brief Encode a proximitysensor struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param proximitysensor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_proximitysensor_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_proximitysensor_t* proximitysensor)
{
    return mavlink_msg_proximitysensor_pack_status(system_id, component_id, _status, msg,  proximitysensor->Proximity);
}

/**
 * @brief Send a proximitysensor message
 * @param chan MAVLink channel to send the message
 *
 * @param Proximity  ProximitySensor
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_proximitysensor_send(mavlink_channel_t chan, double Proximity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ProximitySensor_LEN];
    _mav_put_double(buf, 0, Proximity);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ProximitySensor, buf, MAVLINK_MSG_ID_ProximitySensor_MIN_LEN, MAVLINK_MSG_ID_ProximitySensor_LEN, MAVLINK_MSG_ID_ProximitySensor_CRC);
#else
    mavlink_proximitysensor_t packet;
    packet.Proximity = Proximity;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ProximitySensor, (const char *)&packet, MAVLINK_MSG_ID_ProximitySensor_MIN_LEN, MAVLINK_MSG_ID_ProximitySensor_LEN, MAVLINK_MSG_ID_ProximitySensor_CRC);
#endif
}

/**
 * @brief Send a proximitysensor message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_proximitysensor_send_struct(mavlink_channel_t chan, const mavlink_proximitysensor_t* proximitysensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_proximitysensor_send(chan, proximitysensor->Proximity);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ProximitySensor, (const char *)proximitysensor, MAVLINK_MSG_ID_ProximitySensor_MIN_LEN, MAVLINK_MSG_ID_ProximitySensor_LEN, MAVLINK_MSG_ID_ProximitySensor_CRC);
#endif
}

#if MAVLINK_MSG_ID_ProximitySensor_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_proximitysensor_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double Proximity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, Proximity);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ProximitySensor, buf, MAVLINK_MSG_ID_ProximitySensor_MIN_LEN, MAVLINK_MSG_ID_ProximitySensor_LEN, MAVLINK_MSG_ID_ProximitySensor_CRC);
#else
    mavlink_proximitysensor_t *packet = (mavlink_proximitysensor_t *)msgbuf;
    packet->Proximity = Proximity;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ProximitySensor, (const char *)packet, MAVLINK_MSG_ID_ProximitySensor_MIN_LEN, MAVLINK_MSG_ID_ProximitySensor_LEN, MAVLINK_MSG_ID_ProximitySensor_CRC);
#endif
}
#endif

#endif

// MESSAGE ProximitySensor UNPACKING


/**
 * @brief Get field Proximity from proximitysensor message
 *
 * @return  ProximitySensor
 */
static inline double mavlink_msg_proximitysensor_get_Proximity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Decode a proximitysensor message into a struct
 *
 * @param msg The message to decode
 * @param proximitysensor C-struct to decode the message contents into
 */
static inline void mavlink_msg_proximitysensor_decode(const mavlink_message_t* msg, mavlink_proximitysensor_t* proximitysensor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    proximitysensor->Proximity = mavlink_msg_proximitysensor_get_Proximity(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ProximitySensor_LEN? msg->len : MAVLINK_MSG_ID_ProximitySensor_LEN;
        memset(proximitysensor, 0, MAVLINK_MSG_ID_ProximitySensor_LEN);
    memcpy(proximitysensor, _MAV_PAYLOAD(msg), len);
#endif
}
