// MESSAGE TiltSensor support class

#pragma once

namespace mavlink {
namespace selfio {
namespace msg {

/**
 * @brief TiltSensor message
 *
 * 倾斜传感器
 */
struct TiltSensor : mavlink::Message {
    static constexpr msgid_t MSG_ID = 56109;
    static constexpr size_t LENGTH = 16;
    static constexpr size_t MIN_LENGTH = 16;
    static constexpr uint8_t CRC_EXTRA = 98;
    static constexpr auto NAME = "TiltSensor";


    double Tilt_X; /*<  TiltSensor_X */
    double Tilt_Y; /*<  TiltSensor_Y */


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
        ss << "  Tilt_X: " << Tilt_X << std::endl;
        ss << "  Tilt_Y: " << Tilt_Y << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << Tilt_X;                        // offset: 0
        map << Tilt_Y;                        // offset: 8
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> Tilt_X;                        // offset: 0
        map >> Tilt_Y;                        // offset: 8
    }
};

} // namespace msg
} // namespace selfio
} // namespace mavlink
