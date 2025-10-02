// MESSAGE ambientLight support class

#pragma once

namespace mavlink {
namespace selfio {
namespace msg {

/**
 * @brief ambientLight message
 *
 * 环境光
 */
struct ambientLight : mavlink::Message {
    static constexpr msgid_t MSG_ID = 56106;
    static constexpr size_t LENGTH = 8;
    static constexpr size_t MIN_LENGTH = 8;
    static constexpr uint8_t CRC_EXTRA = 232;
    static constexpr auto NAME = "ambientLight";


    double ambientLight; /*<  ambientLight */


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
        ss << "  ambientLight: " << ambientLight << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << ambientLight;                  // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> ambientLight;                  // offset: 0
    }
};

} // namespace msg
} // namespace selfio
} // namespace mavlink
