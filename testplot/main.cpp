//
// Created by x on 2025/9/24.
//
#include <QDateTime>

#include "plotview.h"

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
    "%{if-debug}D %{endif}"
    "%{if-info}I %{endif}"
    "%{if-warning}W %{endif}"
    "%{if-critical}E %{endif}"
    "%{if-fatal}F %{endif}"

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
    );
    qInfo()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<"plot 测试程序运行";
    QApplication a(argc, argv);


    PlotView w(nullptr);
    w.resize(800, 600);


    for (int i = 1; i < 3; i++) {
        QSharedPointer<QCPGraphDataContainer> data(new QCPGraphDataContainer());
        for (int j = 0; j < 50000; j++)
        {
            data->add(QCPGraphData(j, 50 * i * cos((i * 1000 + j) / 5000.0 * 3.14)));
        }
    }
    w.expandAll();
    w.show();
    return QApplication::exec();
}