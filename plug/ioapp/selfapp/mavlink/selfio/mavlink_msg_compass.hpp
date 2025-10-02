// MESSAGE compass support class

#pragma once

namespace mavlink {
namespace selfio {
namespace msg {

/**
 * @brief compass message
 *
 * 罗盘方向
 */
struct compass : mavlink::Message {
    static constexpr msgid_t MSG_ID = 56103;
    static constexpr size_t LENGTH = 8;
    static constexpr size_t MIN_LENGTH = 8;
    static constexpr uint8_t CRC_EXTRA = 38;
    static constexpr auto NAME = "compass";


    double Compass; /*<  Compass */


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
        ss << "  Compass: " << Compass << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << Compass;                       // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> Compass;                       // offset: 0
    }
};

} // namespace msg
} // namespace selfio
} // namespace mavlink
