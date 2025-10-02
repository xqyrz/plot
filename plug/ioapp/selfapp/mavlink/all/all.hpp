/** @file
 *	@brief MAVLink comm protocol generated from all.xml
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
namespace all {

/**
 * Array of msg_entry needed for @p mavlink_parse_char() (through @p mavlink_get_msg_entry())
 */
constexpr std::array<mavlink_msg_entry_t, 1> MESSAGE_ENTRIES {{ {56000, 25, 8, 8, 0, 0, 0} }};

//! MAVLINK VERSION
constexpr auto MAVLINK_VERSION = 2;


// ENUM DEFINITIONS


/** @brief Commands to be executed by the MAV. They can be executed on user request, or as part of a mission script. If the action is used in a mission, the parameter mapping to the waypoint/mission message is as follows: Param 1, Param 2, Param 3, Param 4, X: Param 5, Y:Param 6, Z:Param 7. This command list is similar what ARINC 424 is for commercial aircraft: A data format how to interpret waypoint/mission data. NaN and INT32_MAX may be used in float/integer params (respectively) to indicate optional/default values (e.g. to use the component's current yaw or latitude rather than a specific value). See https://mavlink.io/en/guide/xml_schema.html#MAV_CMD for information about the structure of the MAV_CMD entries */
enum class MAV_CMD
{
    DUMMY_ALL=393, /* Dummy/temporary MAV_CMD that causes all.xml to correctly import all commands from both ardupilotmega.xml and development.xml (otherwise only one is imported, for the reasons given in https://github.com/ArduPilot/pymavlink/pull/544#discussion_r2069976980).
                    It not be used, and will be removed when the toolchain is fixed. |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
};

//! MAV_CMD ENUM_END
constexpr auto MAV_CMD_ENUM_END = 394;


} // namespace all
} // namespace mavlink

// MESSAGE DEFINITIONS


// base include
#include "../selfio/selfio.hpp"
