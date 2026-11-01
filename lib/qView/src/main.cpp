#include "imageview.h"
#include "qvapplication.h"
#include "qvwin32functions.h"

#include <QCommandLineParser>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setOrganizationName("qView");
    QCoreApplication::setApplicationName("qView");
//    QCoreApplication::setApplicationVersion(QString::number(VERSION));
    QApplication app(argc, argv);
    ImageView view;
    view.show();

    return QApplication::exec();
}
