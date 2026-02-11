//
// Created by 25137 on 25-9-27.
//

#ifndef PLOTCOMMON_H
#define PLOTCOMMON_H
#include <QLoggingCategory>
#include "../plug/ioapp/ioappcommon.h"
#define APP_NAME "plot"
// Q_DECLARE_LOGGING_CATEGORY(plot)
// Q_LOGGING_CATEGORY(plot,APP_NAME)
// #define debugPlot qCDebug(plot)
// #define infoPlot qCInfo(plot)
// #define warningPlot qCWarning(plot)
// #define criticalPlot qCCritical(plot)


namespace PLOT
{
    static const char* const PLOT_COMPANY = "XQYR";
    static const char* const PLOT_PRODUCT = "plot";
    static const char* const color[16] = {
        "#800808",
        "#008000",
        "#888888",
        "#080808",
        "#008080",
        "#808000",
        "#800080",
        "#808080",
        "#000088",
        "#088808",
        "#880000",
        "#008888",
        "#888800",
        "#880088",

        "#088088",
        "#000080",
    };

    typedef enum
    {
        TYPE_oneXoneY,
        TYPE_oneXmoreY,
        TYPE_moreXmoreY
    } PlotType;

    typedef enum
    {
        ITEM_GRAPH,
        ITEM_AXIS,
    } ItemType;
}
#endif //PLOTCOMMON_H
