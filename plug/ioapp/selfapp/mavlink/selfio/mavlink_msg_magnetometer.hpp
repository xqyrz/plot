// MESSAGE magnetometer support class

#pragma once

namespace mavlink {
namespace selfio {
namespace msg {

/**
 * @brief magnetometer message
 *
 * 磁力计
 */
struct magnetometer : mavlink::Message {
    static constexpr msgid_t MSG_ID = 56104;
    static constexpr size_t LENGTH = 24;
    static constexpr size_t MIN_LENGTH = 24;
    static constexpr uint8_t CRC_EXTRA = 144;
    static constexpr auto NAME = "magnetometer";


    double MAG_X; /*<  MAG_X */
    double MAG_Y; /*<  MAG_Y */
    double MAG_Z; /*<  MAG_Z */


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
        ss << "  MAG_X: " << MAG_X << std::endl;
        ss << "  MAG_Y: " << MAG_Y << std::endl;
        ss << "  MAG_Z: " << MAG_Z << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << MAG_X;                         // offset: 0
        map << MAG_Y;                         // offset: 8
        map << MAG_Z;                         // offset: 16
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> MAG_X;                         // offset: 0
        map >> MAG_Y;                         // offset: 8
        map >> MAG_Z;                         // offset: 16
    }
};

} // namespace msg
} // namespace selfio
} // namespace mavlink
