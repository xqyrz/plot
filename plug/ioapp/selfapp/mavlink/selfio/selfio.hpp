/** @file
 *	@brief MAVLink comm protocol generated from selfio.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <array>
#include <cstdint>
#include <sstream>

#ifndef MAVLINK_STX
#define MAVLINK_STX 253
#endif

#include "../message.hpp"

namespace mavlink {
namespace selfio {

/**
 * Array of msg_entry needed for @p mavlink_parse_char() (through @p mavlink_get_msg_entry())
 */
constexpr std::array<mavlink_msg_entry_t, 11> MESSAGE_ENTRIES {{ {56000, 25, 8, 8, 0, 0, 0}, {56101, 193, 24, 24, 0, 0, 0}, {56102, 185, 24, 24, 0, 0, 0}, {56103, 38, 8, 8, 0, 0, 0}, {56104, 144, 24, 24, 0, 0, 0}, {56105, 53, 8, 8, 0, 0, 0}, {56106, 232, 8, 8, 0, 0, 0}, {56107, 250, 8, 8, 0, 0, 0}, {56108, 165, 8, 8, 0, 0, 0}, {56109, 98, 16, 16, 0, 0, 0}, {56110, 186, 16, 16, 0, 0, 0} }};

//! MAVLINK VERSION
constexpr auto MAVLINK_VERSION = 3;


// ENUM DEFINITIONS




} // namespace selfio
} // namespace mavlink

// MESSAGE DEFINITIONS
#include "./mavlink_msg_sensor.hpp"
#include "./mavlink_msg_gyroscope.hpp"
#include "./mavlink_msg_accelerometer.hpp"
#include "./mavlink_msg_compass.hpp"
#include "./mavlink_msg_magnetometer.hpp"
#include "./mavlink_msg_lightsensor.hpp"
#include "./mavlink_msg_ambientlight.hpp"
#include "./mavlink_msg_proximitysensor.hpp"
#include "./mavlink_msg_orientationsensor.hpp"
#include "./mavlink_msg_tiltsensor.hpp"
#include "./mavlink_msg_gps.hpp"

// base include

