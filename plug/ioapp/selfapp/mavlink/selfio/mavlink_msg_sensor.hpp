// MESSAGE sensor support class

#pragma once

namespace mavlink {
namespace selfio {
namespace msg {

/**
 * @brief sensor message
 *
 * Test all field types
 */
struct sensor : mavlink::Message {
    static constexpr msgid_t MSG_ID = 56000;
    static constexpr size_t LENGTH = 8;
    static constexpr size_t MIN_LENGTH = 8;
    static constexpr uint8_t CRC_EXTRA = 25;
    static constexpr auto NAME = "sensor";


    double sensor1; /*<  sensor1 value */


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
        ss << "  sensor1: " << sensor1 << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << sensor1;                       // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> sensor1;                       // offset: 0
    }
};

} // namespace msg
} // namespace selfio
} // namespace mavlink
