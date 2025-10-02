/** @file
 *  @brief MAVLink comm protocol generated from selfio.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_SELFIO_H
#define MAVLINK_SELFIO_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_SELFIO.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_SELFIO_XML_HASH -7039119847976874771

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{56000, 25, 8, 8, 0, 0, 0}, {56101, 193, 24, 24, 0, 0, 0}, {56102, 185, 24, 24, 0, 0, 0}, {56103, 38, 8, 8, 0, 0, 0}, {56104, 144, 24, 24, 0, 0, 0}, {56105, 53, 8, 8, 0, 0, 0}, {56106, 232, 8, 8, 0, 0, 0}, {56107, 250, 8, 8, 0, 0, 0}, {56108, 165, 8, 8, 0, 0, 0}, {56109, 98, 16, 16, 0, 0, 0}, {56110, 186, 16, 16, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_SELFIO

// ENUM DEFINITIONS



// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_sensor.h"
#include "./mavlink_msg_gyroscope.h"
#include "./mavlink_msg_accelerometer.h"
#include "./mavlink_msg_compass.h"
#include "./mavlink_msg_magnetometer.h"
#include "./mavlink_msg_lightsensor.h"
#include "./mavlink_msg_ambientlight.h"
#include "./mavlink_msg_proximitysensor.h"
#include "./mavlink_msg_orientationsensor.h"
#include "./mavlink_msg_tiltsensor.h"
#include "./mavlink_msg_gps.h"

// base include



#if MAVLINK_SELFIO_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_sensor, MAVLINK_MESSAGE_INFO_gyroscope, MAVLINK_MESSAGE_INFO_accelerometer, MAVLINK_MESSAGE_INFO_compass, MAVLINK_MESSAGE_INFO_magnetometer, MAVLINK_MESSAGE_INFO_lightSensor, MAVLINK_MESSAGE_INFO_ambientLight, MAVLINK_MESSAGE_INFO_ProximitySensor, MAVLINK_MESSAGE_INFO_OrientationSensor, MAVLINK_MESSAGE_INFO_TiltSensor, MAVLINK_MESSAGE_INFO_GPS}
# define MAVLINK_MESSAGE_NAMES {{ "GPS", 56110 }, { "OrientationSensor", 56108 }, { "ProximitySensor", 56107 }, { "TiltSensor", 56109 }, { "accelerometer", 56102 }, { "ambientLight", 56106 }, { "compass", 56103 }, { "gyroscope", 56101 }, { "lightSensor", 56105 }, { "magnetometer", 56104 }, { "sensor", 56000 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_SELFIO_H
