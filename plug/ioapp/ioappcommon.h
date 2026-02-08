//
// Created by hw on 2025/10/2.
//

#ifndef PLOT_IOAPPCOMMON_H
#define PLOT_IOAPPCOMMON_H
#include <QObject>
#include <QDateTime>
namespace IOAPP
{
    enum {
        SELFIO_ID = 1,
        VAFA_ID = 2,
    };
    struct SIGNALS {
        union {
            struct {  // 给匿名 struct 一个名字 s
                uint32_t id:32;
                uint16_t type:16;
                uint16_t res:16;
            } ID;
            uint64_t id;
        };
        uint64_t time;
        std::string name;
        std::string unit;

        double value{};

        // 构造函数初始化
        SIGNALS() : ID{0,0,0},time(0) {}
    };

}
#endif //PLOT_IOAPPCOMMON_H