//
// Created by 25137 on 2026/10/14.
//

#ifndef INTERFACECOMMON_H
#define INTERFACECOMMON_H
#include <QString>
#include <QDateTime>
#if defined(P_LIBRARY)
#  define P_EXPORT Q_DECL_EXPORT
#else
#  define P_EXPORT Q_DECL_IMPORT
#endif
namespace PLUG{

    enum class InputType {          // 更好的命名
        IN_VIRTUAL_TX=0,
        IN_IO_TX,
        IN_IO_RX,
        IN_APP_TX,
        IN_APP_RX,
        IN_APP_SIGNAL
    };

    enum class OutputType {        // 更好的命名
        OUT_IO_TX=0,
        OUT_IO_RX,
        OUT_APP_TX,
        OUT_APP_RX,
        OUT_APP_SIGNAL,
    };

    enum class  Type
    {
        Default,
        VIEW,
        IO,
        IOAPP,
        SIGNAL,
    };
    inline const char* TypeStr(Type type)
    {
        switch (type)
        {
        case Type::VIEW:return "VIEW";
        case Type::IO:return "IO";
        case Type::IOAPP:return "IOAPP";
        case Type::SIGNAL:return "SIGNAL";
        case Type::Default:return "Default";
        default: return "UNKNOW";
        }
    }


    typedef struct {
        QString dev;//设备 ip
        QString ch;//通道
        QString own_dev; //自己
        QString own_ch;
    }Config;
    enum class  RT
    {
        RX,
        TX
    };
    class Frame{
    public:
        Config  info;//发送设备的信息
        QDateTime time;
        RT RT;
        QByteArray data;
    };
    typedef enum
    {
        OPEN_STATUS,
        CLOSE_STATUS,
        FAIL_STATUS
    }STATUS;

    enum {
        SELFIO_ID = 1,
        VAFA_ID = 2,
    };
    struct _SIGNALS {
        union {
            struct {  // 给匿名 struct 一个名字 s
                uint32_t id:32;
                uint16_t type:16;
                uint16_t res:16;
            } ID;
            uint64_t id;
        };
        double time;
        double dTime;
        std::string name;
        std::string unit;

        double value{};

        // 构造函数初始化
        _SIGNALS() : ID{0,0,0},time(0) {}
    };
}
Q_DECLARE_METATYPE(PLUG::Frame)
#endif // PLOT_INTERFACECOMMON_H
