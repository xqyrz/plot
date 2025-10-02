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
constexpr std::array<mavlink_msg_entry_t, 1> MESSAGE_ENTRIES {{ {56000, 25, 8, 8, 0, 0, 0} }};

//! MAVLINK VERSION
constexpr auto MAVLINK_VERSION = 3;


// ENUM DEFINITIONS




} // namespace selfio
} // namespace mavlink

// MESSAGE DEFINITIONS
#include "./mavlink_msg_sensor.hpp"

// base include

