//
// Created by hw on 2025/10/2.
//

#ifndef PLOT_IOAPPCOMMON_H
#define PLOT_IOAPPCOMMON_H
#include <QObject>
#include <QDateTime>
namespace IOAPP
{
    struct SIGNALS {
        union {
            struct {  // 给匿名 struct 一个名字 s
                uint32_t res:32;
                uint16_t type:16;
                uint16_t index:16;
                uint64_t subindex;
            } ID;
            __uint128_t id;
        };
        QDateTime time;
        std::string name;
        std::string unit;
        double value{};

        // 构造函数初始化
        SIGNALS() : ID{0,0,0,0} {}
    };

}
#endif //PLOT_IOAPPCOMMON_H