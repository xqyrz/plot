//
// Created by 25137 on 25-9-27.
//

#ifndef PLOTCOMMON_H
#define PLOTCOMMON_H
#include <QLoggingCategory>
#define APP_NAME "plot"
// Q_DECLARE_LOGGING_CATEGORY(plot)
// Q_LOGGING_CATEGORY(plot,APP_NAME)
// #define debugPlot qCDebug(plot)
// #define infoPlot qCInfo(plot)
// #define warningPlot qCWarning(plot)
// #define criticalPlot qCCritical(plot)

//TODO:从CANOE中获得颜色
namespace PLOT {
    static const  char* const PLOT_COMPANY = "XQYR";
    static const  char* const PLOT_PRODUCT = "plot";
    static const  char* const color[16] = {
        "#008000",
        "#33cccc",
        "#ff6600",
        "#000080",
        "#99ccff",
        "#FF0000",
        "#108b96",
        "#800000",
        "#800008",
        "#800080",
        "#808800",
        "#808000",
        "#880000",
        "#880080",
        "#880800",
        "#888000",
    };
    typedef enum  {
       TYPE_oneXoneY,
        TYPE_oneXmoreY,
        TYPE_moreXmoreY
    }PlotType;
}
#endif //PLOTCOMMON_H
