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

TEST(selfio, gyroscope)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::gyroscope packet_in{};
    packet_in.GYRO_X = 123.0;
    packet_in.GYRO_Y = 179.0;
    packet_in.GYRO_Z = 235.0;

    mavlink::selfio::msg::gyroscope packet1{};
    mavlink::selfio::msg::gyroscope packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.GYRO_X, packet2.GYRO_X);
    EXPECT_EQ(packet1.GYRO_Y, packet2.GYRO_Y);
    EXPECT_EQ(packet1.GYRO_Z, packet2.GYRO_Z);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, gyroscope)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_gyroscope_t packet_c {
         123.0, 179.0, 235.0
    };

    mavlink::selfio::msg::gyroscope packet_in{};
    packet_in.GYRO_X = 123.0;
    packet_in.GYRO_Y = 179.0;
    packet_in.GYRO_Z = 235.0;

    mavlink::selfio::msg::gyroscope packet2{};

    mavlink_msg_gyroscope_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.GYRO_X, packet2.GYRO_X);
    EXPECT_EQ(packet_in.GYRO_Y, packet2.GYRO_Y);
    EXPECT_EQ(packet_in.GYRO_Z, packet2.GYRO_Z);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(selfio, accelerometer)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::accelerometer packet_in{};
    packet_in.ACC_X = 123.0;
    packet_in.ACC_Y = 179.0;
    packet_in.ACC_Z = 235.0;

    mavlink::selfio::msg::accelerometer packet1{};
    mavlink::selfio::msg::accelerometer packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.ACC_X, packet2.ACC_X);
    EXPECT_EQ(packet1.ACC_Y, packet2.ACC_Y);
    EXPECT_EQ(packet1.ACC_Z, packet2.ACC_Z);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, accelerometer)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_accelerometer_t packet_c {
         123.0, 179.0, 235.0
    };

    mavlink::selfio::msg::accelerometer packet_in{};
    packet_in.ACC_X = 123.0;
    packet_in.ACC_Y = 179.0;
    packet_in.ACC_Z = 235.0;

    mavlink::selfio::msg::accelerometer packet2{};

    mavlink_msg_accelerometer_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.ACC_X, packet2.ACC_X);
    EXPECT_EQ(packet_in.ACC_Y, packet2.ACC_Y);
    EXPECT_EQ(packet_in.ACC_Z, packet2.ACC_Z);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(selfio, compass)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::compass packet_in{};
    packet_in.Compass = 123.0;

    mavlink::selfio::msg::compass packet1{};
    mavlink::selfio::msg::compass packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.Compass, packet2.Compass);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, compass)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_compass_t packet_c {
         123.0
    };

    mavlink::selfio::msg::compass packet_in{};
    packet_in.Compass = 123.0;

    mavlink::selfio::msg::compass packet2{};

    mavlink_msg_compass_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.Compass, packet2.Compass);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(selfio, magnetometer)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::magnetometer packet_in{};
    packet_in.MAG_X = 123.0;
    packet_in.MAG_Y = 179.0;
    packet_in.MAG_Z = 235.0;

    mavlink::selfio::msg::magnetometer packet1{};
    mavlink::selfio::msg::magnetometer packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.MAG_X, packet2.MAG_X);
    EXPECT_EQ(packet1.MAG_Y, packet2.MAG_Y);
    EXPECT_EQ(packet1.MAG_Z, packet2.MAG_Z);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, magnetometer)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_magnetometer_t packet_c {
         123.0, 179.0, 235.0
    };

    mavlink::selfio::msg::magnetometer packet_in{};
    packet_in.MAG_X = 123.0;
    packet_in.MAG_Y = 179.0;
    packet_in.MAG_Z = 235.0;

    mavlink::selfio::msg::magnetometer packet2{};

    mavlink_msg_magnetometer_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.MAG_X, packet2.MAG_X);
    EXPECT_EQ(packet_in.MAG_Y, packet2.MAG_Y);
    EXPECT_EQ(packet_in.MAG_Z, packet2.MAG_Z);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(selfio, lightSensor)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::lightSensor packet_in{};
    packet_in.light = 123.0;

    mavlink::selfio::msg::lightSensor packet1{};
    mavlink::selfio::msg::lightSensor packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.light, packet2.light);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, lightSensor)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_lightsensor_t packet_c {
         123.0
    };

    mavlink::selfio::msg::lightSensor packet_in{};
    packet_in.light = 123.0;

    mavlink::selfio::msg::lightSensor packet2{};

    mavlink_msg_lightsensor_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.light, packet2.light);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(selfio, ambientLight)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::ambientLight packet_in{};
    packet_in.ambientLight = 123.0;

    mavlink::selfio::msg::ambientLight packet1{};
    mavlink::selfio::msg::ambientLight packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.ambientLight, packet2.ambientLight);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, ambientLight)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_ambientlight_t packet_c {
         123.0
    };

    mavlink::selfio::msg::ambientLight packet_in{};
    packet_in.ambientLight = 123.0;

    mavlink::selfio::msg::ambientLight packet2{};

    mavlink_msg_ambientlight_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.ambientLight, packet2.ambientLight);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(selfio, ProximitySensor)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::ProximitySensor packet_in{};
    packet_in.Proximity = 123.0;

    mavlink::selfio::msg::ProximitySensor packet1{};
    mavlink::selfio::msg::ProximitySensor packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.Proximity, packet2.Proximity);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, ProximitySensor)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_proximitysensor_t packet_c {
         123.0
    };

    mavlink::selfio::msg::ProximitySensor packet_in{};
    packet_in.Proximity = 123.0;

    mavlink::selfio::msg::ProximitySensor packet2{};

    mavlink_msg_proximitysensor_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.Proximity, packet2.Proximity);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(selfio, OrientationSensor)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::OrientationSensor packet_in{};
    packet_in.Orientation = 123.0;

    mavlink::selfio::msg::OrientationSensor packet1{};
    mavlink::selfio::msg::OrientationSensor packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.Orientation, packet2.Orientation);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, OrientationSensor)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_orientationsensor_t packet_c {
         123.0
    };

    mavlink::selfio::msg::OrientationSensor packet_in{};
    packet_in.Orientation = 123.0;

    mavlink::selfio::msg::OrientationSensor packet2{};

    mavlink_msg_orientationsensor_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.Orientation, packet2.Orientation);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(selfio, TiltSensor)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::TiltSensor packet_in{};
    packet_in.Tilt_X = 123.0;
    packet_in.Tilt_Y = 179.0;

    mavlink::selfio::msg::TiltSensor packet1{};
    mavlink::selfio::msg::TiltSensor packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.Tilt_X, packet2.Tilt_X);
    EXPECT_EQ(packet1.Tilt_Y, packet2.Tilt_Y);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, TiltSensor)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_tiltsensor_t packet_c {
         123.0, 179.0
    };

    mavlink::selfio::msg::TiltSensor packet_in{};
    packet_in.Tilt_X = 123.0;
    packet_in.Tilt_Y = 179.0;

    mavlink::selfio::msg::TiltSensor packet2{};

    mavlink_msg_tiltsensor_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.Tilt_X, packet2.Tilt_X);
    EXPECT_EQ(packet_in.Tilt_Y, packet2.Tilt_Y);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(selfio, GPS)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::selfio::msg::GPS packet_in{};
    packet_in.lat = 123.0;
    packet_in.lon = 179.0;

    mavlink::selfio::msg::GPS packet1{};
    mavlink::selfio::msg::GPS packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.lat, packet2.lat);
    EXPECT_EQ(packet1.lon, packet2.lon);
}

#ifdef TEST_INTEROP
TEST(selfio_interop, GPS)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_gps_t packet_c {
         123.0, 179.0
    };

    mavlink::selfio::msg::GPS packet_in{};
    packet_in.lat = 123.0;
    packet_in.lon = 179.0;

    mavlink::selfio::msg::GPS packet2{};

    mavlink_msg_gps_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.lat, packet2.lat);
    EXPECT_EQ(packet_in.lon, packet2.lon);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
