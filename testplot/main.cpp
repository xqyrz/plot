//
// Created by x on 2025/9/24.
//
#include "plottree.h"
#include "plotmodel.h"
int main(int argc, char *argv[])
{
    // qInstallMessageHandler(customMessageHandler);
    qSetMessagePattern(
    // 基础信息（所有日志级别共有）
    "%{time process} "
    "[%{threadid}] "
#ifdef  QT_DEBUG
    // Debug 信息（青色）
    "%{if-debug}\033[32m%{endif}"

    // Info 信息（绿色）
    "%{if-info}\033[37m%{endif}"

    // Warning 信息（黄色）
    "%{if-warning}\033[33m%{endif}"

    // Critical 信息（红色）
    "%{if-critical}\033[31m%{endif}"

    // Fatal 信息（红色加粗+背景高亮）
    "%{if-fatal}\033[41;1m%{endif}"
#endif
    // 日志类型标签（带条件颜色）
    "%{if-debug}[DBUG] %{endif}"
    "%{if-info}[INFO] %{endif}"
    "%{if-warning}[WARN] %{endif}"
    "%{if-critical}[ERR ] %{endif}"
    "%{if-fatal}[FATAL]%{endif}"

    // 可选：应用模块分类
    "%{if-category}%{category}:%{endif}"
#ifdef  QT_DEBUG
    // 源代码位置（调试用）
    "%{file}:%{line} - "
#endif
    // 日志消息主体
    "%{message}"
#ifdef  QT_DEBUG
    // 重置颜色（所有带颜色的日志都需要）
    "\033[0m"
#endif
    // 致命错误追加调用栈（需启用 QT_MESSAGE_PATTERN 环境变量）
    //"%{if-fatal}\nBacktrace: %{backtrace depth=20 separator=\"\n\"}%{endif}"
    );
    QApplication a(argc, argv);
    //testPlot w;
    PlotTree w(nullptr);
    PlotModel*model=new PlotModel();
    w.setModel(model);
    w.resize(800, 600);


    w.show();

    return QApplication::exec();
}