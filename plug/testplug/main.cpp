//
// Created by 25137 on 25-10-1.
//
#include "../io/iointerface.h"
#include "../ioapp/ioappinterface.h"
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QPluginLoader>
#include <QTimer>
#include "plotview.h"
#include <QMutexLocker>

#include <QMutex>

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
    );
    qInfo()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<"plug run";
    QApplication a(argc, argv);
    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() +"/lib");



    QDir path = QDir( QCoreApplication::applicationDirPath());
    path.cd("../install/plug");
    IOInterface* tcpServer{nullptr};
    IOInterface* tcpClient{nullptr};
    IOInterface* udp{nullptr};
    IOAPPInterface* selfio{nullptr};
    foreach(QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {

        QPluginLoader pluginLoader(info.absoluteFilePath());
        QObject* plugin = pluginLoader.instance();
        if (plugin)
        {
            // 获取元数据（名称、版本、依赖）

            QJsonObject meta = pluginLoader.metaData();
            //qDebug()<<meta;
            auto json = meta.value("MetaData").toObject();
            auto iid = meta.value("IID").toString();
            auto className = meta.value("className").toString();
            qInfo() << QString("**********  %1 %2:%3   **********").arg(info.baseName(),iid,className);

// ;            qDebug() << json.value("author").toString();
//             qDebug() << json.value("date").toString();
//             qDebug() << json.value("version").toString();
            //qDebug() << json.value("dependencies").toArray().toVariantList();
            //访问感兴趣的接口
            if (iid == IOInterface_Id)
            {
                if (className == "ATCPServer")
                {
                    tcpServer = qobject_cast<IOInterface*>(plugin);
                    tcpServer->setConfig(IO::Config{"127.0.0.1","1234"});
                  //  tcpServer->open();
                }
                else if (className == "ATCPClient") {
                    tcpClient= qobject_cast<IOInterface*>(plugin);
                    tcpClient->setConfig(IO::Config{"127.0.0.1","1234"});
                }
                else if (className == "AUdp") {
                    udp =  qobject_cast<IOInterface*>(plugin);
                    udp->setConfig(IO::Config{""
                        ,"6123"
                    });
                    udp->open();
                }
            }
            else if (iid == IOAPPInterface_Id)
            {
                if (className == "SelfIOAPP")
                {
                    selfio = qobject_cast<IOAPPInterface*>(plugin);
                }
            }
        }
    }
    
    //tcpClient->open();
    QTimer timer;
    QObject::connect(&timer,&QTimer::timeout,[=]()
    {
        auto frame = selfio->encode();
        tcpClient->write(frame);
    });

    PlotView w(nullptr);
    w.resize(800, 600);

    w.expandAll();
    w.show();
    QMutex mutex;
    udp->setReadReadyCallback([&](int)
    {
      //  QMutexLocker locker(&mutex);
    auto frams = udp->readALL();

    foreach(auto const & var,frams)
    {
      auto sigs =  selfio->decode(var);
        if (sigs.size() ) {
            w.enupRang();
            w.addSignalData(sigs);
        }
    }
});
    return QApplication::exec();
}
