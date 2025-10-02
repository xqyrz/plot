// MESSAGE gyroscope support class

#pragma once

namespace mavlink {
namespace selfio {
namespace msg {

/**
 * @brief gyroscope message
 *
 * 陀螺仪
 */
struct gyroscope : mavlink::Message {
    static constexpr msgid_t MSG_ID = 56101;
    static constexpr size_t LENGTH = 24;
    static constexpr size_t MIN_LENGTH = 24;
    static constexpr uint8_t CRC_EXTRA = 193;
    static constexpr auto NAME = "gyroscope";


    double GYRO_X; /*<  GYRO_X */
    double GYRO_Y; /*<  GYRO_Y */
    double GYRO_Z; /*<  GYRO_Z */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  GYRO_X: " << GYRO_X << std::endl;
        ss << "  GYRO_Y: " << GYRO_Y << std::endl;
        ss << "  GYRO_Z: " << GYRO_Z << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << GYRO_X;                        // offset: 0
        map << GYRO_Y;                        // offset: 8
        map << GYRO_Z;                        // offset: 16
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> GYRO_X;                        // offset: 0
        map >> GYRO_Y;                        // offset: 8
        map >> GYRO_Z;                        // offset: 16
    }
};

} // namespace msg
} // namespace selfio
} // namespace mavlink
