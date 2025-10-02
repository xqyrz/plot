/** @file
 *	@brief MAVLink comm testsuite protocol generated from selfio.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "selfio.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(selfio, sensor)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::sensor packet_in{};
    packet_in.sensor1 = 123.0;

    mavlink::selfio::msg::sensor packet1{};
    mavlink::selfio::msg::sensor packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.sensor1, packet2.sensor1);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, sensor)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_sensor_t packet_c {
         123.0
    };

    mavlink::selfio::msg::sensor packet_in{};
    packet_in.sensor1 = 123.0;

    mavlink::selfio::msg::sensor packet2{};

    mavlink_msg_sensor_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.sensor1, packet2.sensor1);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
