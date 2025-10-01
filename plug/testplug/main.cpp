//
// Created by 25137 on 25-10-1.
//
#include "../io/iointerface.h"
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QPluginLoader>
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
    // 致命错误追加调用栈（需启用 QT_MESSAGE_PATTERN 环境变量）
    //"%{if-fatal}\nBacktrace: %{backtrace depth=20 separator=\"\n\"}%{endif}"
    );
    //qputenv("QT_LOGGING_RULES", "plot.debug=false");
    qInfo()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<"plug 测试程序运行";
    QCoreApplication a(argc, argv);
    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() +"/lib");



    QDir path = QDir( QCoreApplication::applicationDirPath());
   path.cd("../lib");
    foreach(QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
        qDebug() << info;
        QPluginLoader pluginLoader(info.absoluteFilePath());
        QObject* plugin = pluginLoader.instance();
        if (plugin)
        {
            // 获取元数据（名称、版本、依赖）

            QJsonObject json = pluginLoader.metaData().value("MetaData").toObject();
            qDebug() << "********** MetaData **********";
            qDebug() << json.value("author").toVariant();
            qDebug() << json.value("date").toVariant();
            qDebug() << json.value("name").toVariant();
            qDebug() << json.value("version").toVariant();
            //qDebug() << json.value("dependencies").toArray().toVariantList();
            //访问感兴趣的接口
           auto app = qobject_cast<IOInterface*>(plugin);
            app->open();
            qDebug()<<app->getName();
        }
    }

    return QCoreApplication::exec();
}