/** @file
 *  @brief MAVLink comm protocol generated from all.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_ALL_H
#define MAVLINK_ALL_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_ALL.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_ALL_XML_HASH -759200316631544531

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{56000, 25, 8, 8, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_ALL

// ENUM DEFINITIONS


/** @brief Commands to be executed by the MAV. They can be executed on user request, or as part of a mission script. If the action is used in a mission, the parameter mapping to the waypoint/mission message is as follows: Param 1, Param 2, Param 3, Param 4, X: Param 5, Y:Param 6, Z:Param 7. This command list is similar what ARINC 424 is for commercial aircraft: A data format how to interpret waypoint/mission data. NaN and INT32_MAX may be used in float/integer params (respectively) to indicate optional/default values (e.g. to use the component's current yaw or latitude rather than a specific value). See https://mavlink.io/en/guide/xml_schema.html#MAV_CMD for information about the structure of the MAV_CMD entries */
#ifndef HAVE_ENUM_MAV_CMD
#define HAVE_ENUM_MAV_CMD
typedef enum MAV_CMD
{
   MAV_CMD_DUMMY_ALL=393, /* Dummy/temporary MAV_CMD that causes all.xml to correctly import all commands from both ardupilotmega.xml and development.xml (otherwise only one is imported, for the reasons given in https://github.com/ArduPilot/pymavlink/pull/544#discussion_r2069976980).
                    It not be used, and will be removed when the toolchain is fixed. |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_ENUM_END=394, /*  | */
} MAV_CMD;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS


// base include
#include "../selfio/selfio.h"


#if MAVLINK_ALL_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_sensor}
# define MAVLINK_MESSAGE_NAMES {{ "sensor", 56000 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_ALL_H
