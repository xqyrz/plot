
#include <QApplication>
#include <QPluginLoader>
#include <QWidget>
#include <qfileinfo.h>
#include <QTextCodec>
#include <QDir>
#include "ajlinkarm/ajlinkarm.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    qDebug()<<PLUG_PATH;
    QPluginLoader pluginLoader(QString(PLUG_PATH));
    if (auto plugin = pluginLoader.instance())
    {
        QJsonObject meta = pluginLoader.metaData();
        // qDebug()<<meta;
        auto json = meta.value("MetaData").toObject();
        auto iid = meta.value("IID").toString();
        auto className = meta.value("className").toString();
        qInfo() << QString("**********  %1 %2:%3   **********").arg(PLUG_PATH, iid, className);
        auto jlink = static_cast<AJLinkArm*>(plugin);
        jlink->open();
        jlink->run();
    }
    else
    {
        QByteArray rawData = pluginLoader.errorString().toLatin1();
        QTextCodec *gbk = QTextCodec::codecForName("GBK");
        QString chineseMsg = gbk->toUnicode(rawData);
        qDebug() << "Failed to load plugin:" << chineseMsg;
        QString pluginDir = QFileInfo(PLUG_PATH).path();
        qDebug() << "Plugin directory:" << pluginDir;

        // 列出 Qt 相关的 DLL
        QStringList qtDlls = QDir(pluginDir).entryList(QStringList() << "Qt*.dll" << "*.dll");
        qDebug() << "DLLs in plugin dir:" << qtDlls;
    }
    w.show();
    return a.exec();
}