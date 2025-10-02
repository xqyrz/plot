// MESSAGE accelerometer support class

#pragma once

namespace mavlink {
namespace selfio {
namespace msg {

/**
 * @brief accelerometer message
 *
 * 加速度
 */
struct accelerometer : mavlink::Message {
    static constexpr msgid_t MSG_ID = 56102;
    static constexpr size_t LENGTH = 24;
    static constexpr size_t MIN_LENGTH = 24;
    static constexpr uint8_t CRC_EXTRA = 185;
    static constexpr auto NAME = "accelerometer";


    double ACC_X; /*<  ACC_X */
    double ACC_Y; /*<  ACC_Y */
    double ACC_Z; /*<  ACC_Z */


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
        ss << "  ACC_X: " << ACC_X << std::endl;
        ss << "  ACC_Y: " << ACC_Y << std::endl;
        ss << "  ACC_Z: " << ACC_Z << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << ACC_X;                         // offset: 0
        map << ACC_Y;                         // offset: 8
        map << ACC_Z;                         // offset: 16
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> ACC_X;                         // offset: 0
        map >> ACC_Y;                         // offset: 8
        map >> ACC_Z;                         // offset: 16
    }
};

} // namespace msg
} // namespace selfio
} // namespace mavlink
