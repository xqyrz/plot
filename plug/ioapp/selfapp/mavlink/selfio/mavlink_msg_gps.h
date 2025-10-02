#pragma once
// MESSAGE GPS PACKING

#define MAVLINK_MSG_ID_GPS 56110


typedef struct __mavlink_gps_t {
 double lat; /*<  lat*/
 double lon; /*<  lon*/
} mavlink_gps_t;

#define MAVLINK_MSG_ID_GPS_LEN 16
#define MAVLINK_MSG_ID_GPS_MIN_LEN 16
#define MAVLINK_MSG_ID_56110_LEN 16
#define MAVLINK_MSG_ID_56110_MIN_LEN 16

#define MAVLINK_MSG_ID_GPS_CRC 186
#define MAVLINK_MSG_ID_56110_CRC 186



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_GPS { \
    56110, \
    "GPS", \
    2, \
    {  { "lat", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_gps_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_gps_t, lon) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_GPS { \
    "GPS", \
    2, \
    {  { "lat", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_gps_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_gps_t, lon) }, \
         } \
}
#endif

/**
 * @brief Pack a gps message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat  lat
 * @param lon  lon
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double lat, double lon)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GPS_LEN];
    _mav_put_double(buf, 0, lat);
    _mav_put_double(buf, 8, lon);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GPS_LEN);
#else
    mavlink_gps_t packet;
    packet.lat = lat;
    packet.lon = lon;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GPS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GPS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GPS_MIN_LEN, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
}

/**
 * @brief Pack a gps message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat  lat
 * @param lon  lon
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double lat, double lon)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GPS_LEN];
    _mav_put_double(buf, 0, lat);
    _mav_put_double(buf, 8, lon);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GPS_LEN);
#else
    mavlink_gps_t packet;
    packet.lat = lat;
    packet.lon = lon;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GPS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GPS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_GPS_MIN_LEN, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_GPS_MIN_LEN, MAVLINK_MSG_ID_GPS_LEN);
#endif
}

/**
 * @brief Pack a gps message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lat  lat
 * @param lon  lon
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double lat,double lon)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GPS_LEN];
    _mav_put_double(buf, 0, lat);
    _mav_put_double(buf, 8, lon);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GPS_LEN);
#else
    mavlink_gps_t packet;
    packet.lat = lat;
    packet.lon = lon;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GPS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GPS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GPS_MIN_LEN, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
}

/**
 * @brief Encode a gps struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gps_t* gps)
{
    return mavlink_msg_gps_pack(system_id, component_id, msg, gps->lat, gps->lon);
}

/**
 * @brief Encode a gps struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gps_t* gps)
{
    return mavlink_msg_gps_pack_chan(system_id, component_id, chan, msg, gps->lat, gps->lon);
}

/**
 * @brief Encode a gps struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_gps_t* gps)
{
    return mavlink_msg_gps_pack_status(system_id, component_id, _status, msg,  gps->lat, gps->lon);
}

/**
 * @brief Send a gps message
 * @param chan MAVLink channel to send the message
 *
 * @param lat  lat
 * @param lon  lon
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gps_send(mavlink_channel_t chan, double lat, double lon)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GPS_LEN];
    _mav_put_double(buf, 0, lat);
    _mav_put_double(buf, 8, lon);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, buf, MAVLINK_MSG_ID_GPS_MIN_LEN, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#else
    mavlink_gps_t packet;
    packet.lat = lat;
    packet.lon = lon;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, (const char *)&packet, MAVLINK_MSG_ID_GPS_MIN_LEN, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#endif
}

/**
 * @brief Send a gps message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gps_send_struct(mavlink_channel_t chan, const mavlink_gps_t* gps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gps_send(chan, gps->lat, gps->lon);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, (const char *)gps, MAVLINK_MSG_ID_GPS_MIN_LEN, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#endif
}

#if MAVLINK_MSG_ID_GPS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gps_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double lat, double lon)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, lat);
    _mav_put_double(buf, 8, lon);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, buf, MAVLINK_MSG_ID_GPS_MIN_LEN, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#else
    mavlink_gps_t *packet = (mavlink_gps_t *)msgbuf;
    packet->lat = lat;
    packet->lon = lon;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, (const char *)packet, MAVLINK_MSG_ID_GPS_MIN_LEN, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#endif
}
#endif

#endif

// MESSAGE GPS UNPACKING


/**
 * @brief Get field lat from gps message
 *
 * @return  lat
 */
static inline double mavlink_msg_gps_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Get field lon from gps message
 *
 * @return  lon
 */
static inline double mavlink_msg_gps_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  8);
}

/**
 * @brief Decode a gps message into a struct
 *
 * @param msg The message to decode
 * @param gps C-struct to decode the message contents into
 */
static inline void mavlink_msg_gps_decode(const mavlink_message_t* msg, mavlink_gps_t* gps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    gps->lat = mavlink_msg_gps_get_lat(msg);
    gps->lon = mavlink_msg_gps_get_lon(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_GPS_LEN? msg->len : MAVLINK_MSG_ID_GPS_LEN;
        memset(gps, 0, MAVLINK_MSG_ID_GPS_LEN);
    memcpy(gps, _MAV_PAYLOAD(msg), len);
#endif
}
