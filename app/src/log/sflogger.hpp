#pragma once
#include <QtConcurrent/QtConcurrent>
#include <QRegularExpression>
#include <iostream>

inline  const char  Red[] = "\033[31m";
inline  const char  Green[] = "\033[32m";
inline  const char  Yellow[] = "\033[33m";
inline  const char  Blue[] = "\033[36m";
inline  const char  White[] = "\033[37m";
inline  const char  ColorEnd[] = "\033[0m";
//QtDebugMsg, QtWarningMsg, QtCriticalMsg, QtFatalMsg, QtInfoMsg, QtSystemMsg
inline const char* logLevel[] = { Green, Yellow,Red,Red,White,Blue};

class SfLogger {

public:
    enum class LOGModle {
        terminalOUT = 0X01,
        fileOUT = 0X02,
        CallBack = 0X04
    };
    Q_DECLARE_FLAGS(LOGModles, LOGModle)
    typedef struct {
        QString time;
        QString info;
        QString msg;
        const char* l;
    }frame;
    static LOGModles modle;
private:
    static const qint64 MAX_FILE_SIZE = 10 * 1024 * 1024;  // 100 MB
    static const int MAX_BACKUP_FILES = 100;  // 最多保留的备份文件数
    SfLogger(QString logfile="defalut_qt_log")
    {
        if(this->logfile.isEmpty()){
            this->logfile = logfile;
        }
        g_startupTimer->start();
        createLogFile();
    }
    SfLogger(const SfLogger &) = delete;
    SfLogger &operator=(const SfLogger &) = delete;
    ~SfLogger() {
        delete g_startupTimer;
        writeFuture.waitForFinished();
        file.close();
    }

    void write() {
        while (true) {
            frame msg;
            {
                QMutexLocker locker(&mutex);
                if (queue.isEmpty()) break;

                msg = queue.dequeue();
            }
            // 检查文件大小
            if (isFileSizeExceeded()) {
                rotateLogFile();
            }
            // 写入日志
            if (file.isOpen()) {
                QTextStream stream(&file);
                //std::cout<<msg.info.toStdString()<<msg.msg.toStdString() << std::endl;
                stream << msg.info <<msg.msg <<Qt::endl;
            }
        }
    }
public:


    inline static QElapsedTimer* getTimer() {return g_startupTimer;};

    inline static QString extractShortFunctionName(const QString& fullFunction) {
    #if 1
        QRegularExpression re(R"(([\w:~]+)\s*\()");
        auto match = re.match(fullFunction);
        if (match.hasMatch())
            return match.captured(1);
        else return fullFunction;
    #else
        // 匹配 类名::函数名 的模式
        static QRegularExpression regex(R"((\w+::\w+))");
        QRegularExpressionMatch match = regex.match(fullFunction);
        if (match.hasMatch()) {
            return match.captured(1);  // 返回 "ClassName::methodName"
        }

        // 如果没有类名，只匹配函数名
        static QRegularExpression funcRegex(R"((\w+)\s*\()");
        QRegularExpressionMatch funcMatch = funcRegex.match(fullFunction);
        if (funcMatch.hasMatch()) {
            return funcMatch.captured(1);
        }

        return fullFunction;
    #endif
    }

    static void customMessageHandler(QtMsgType type,
                                     const QMessageLogContext &context,
                                     const QString &msg) {
        frame formattedMessage;
        formattedMessage.msg = msg;
        formattedMessage.info =     QString("%1 ").arg(g_startupTimer->elapsed() / 1000.0,  // 值
                                                   12,                                   // 字段宽度（含小数点）
                                                   'f',                                 // 定点格式
                                                   3,                                   // 3 位小数
                                                   QLatin1Char(' '));                   // 左侧补空格
        switch (type) {
        case QtDebugMsg:
            formattedMessage.info +="[DEBUG] ";
            break;
        case QtInfoMsg:
            formattedMessage.info += "[INFO ] ";
            break;
        case QtWarningMsg:
            formattedMessage.info += "[WARN ] ";
            break;
        case QtCriticalMsg:
            formattedMessage.info += "[ERROR] ";
            break;
        case QtFatalMsg:
            formattedMessage.info += "[FAIL ] ";
            break;
        default:
            break;
        }
        auto &logger = instance();
        {
            QMutexLocker locker(&logger.mutex);
#ifdef QT_DEBUG
            formattedMessage.msg = QString("[%1:%2] %3")
                                       .arg(extractShortFunctionName(context.function))  // 提取简化的函数名
                                       .arg(context.line)
                                       .arg(formattedMessage.msg);
#endif // DEBUG

            std::cout << logLevel[type] << " "
           << formattedMessage.info.toStdString()
           << formattedMessage.msg.toStdString()
           << " \033[0m"<<std::endl;
            logger.queue.enqueue(formattedMessage);
        }
        if (!logger.writeFuture.isRunning()) {
            logger.writeFuture = QtConcurrent::run(&instance(), &SfLogger::write);
        }
    }

    static SfLogger &instance(QString logFile="defalut_qt_log") {
        static SfLogger logger(logFile);
        return logger;
    }

private:
    void createLogFile() {
        // QString logDirPath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/"+logfile+"/log";
        // qInfo()<<"configDirPath"<<QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
        // qInfo() <<"logDirPath"<< logDirPath;
        QString logDirPath = "./log";
        QDir logDir(logDirPath);
        if (!logDir.exists()) {
            logDir.mkpath(".");
        }

        QString logFilePath = logDirPath + "/" +
                              QDateTime::currentDateTime().toString("yyyy-MM-dd") +
                              ".log";

        file.setFileName(logFilePath);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            qDebug() << "Failed to open log file:" << file.errorString();
        }
        else
        {
            QTextStream stream(&file);
            stream << Qt::endl;
            stream << "Log file created at: "
                   << QDateTime::currentDateTime().toString(Qt::TextDate)<< Qt::endl;
        }
    }

    bool isFileSizeExceeded() const { return file.size() >= MAX_FILE_SIZE; }

    void rotateLogFile() {
        file.close();  // 先关闭当前文件
        QString baseName = QFileInfo(file.fileName()).baseName();
        QString dirPath = QFileInfo(file.fileName()).absolutePath();

        // 查找下一个可用的备份文件名
        for (int i = MAX_BACKUP_FILES; i > 0; --i) {
            QString oldFileName =
                QString("%1/%2-%3.log").arg(dirPath).arg(baseName).arg(i);
            if (QFile::exists(oldFileName)) {
                // 如果存在，则重命名为下一个序号
                if (i == MAX_BACKUP_FILES) {
                    QFile::remove(oldFileName);  // 超过最大文件数，删除最旧的
                } else {
                    QString newFileName =
                        QString("%1/%2-%3.log").arg(dirPath).arg(baseName).arg(i + 1);
                    QFile::rename(oldFileName, newFileName);
                }
            }
        }

        // 将当前日志文件重命名为 -1
        QString newFileName = QString("%1/%2-1.log").arg(dirPath).arg(baseName);
        QFile::rename(file.fileName(), newFileName);

        // 重新创建新日志文件
        createLogFile();
    }

private:

    QMutex mutex;
    QQueue<frame> queue;
    QFuture<void> writeFuture;
    QFile file;
    QString logfile;
    static QElapsedTimer* g_startupTimer;

};
inline  QElapsedTimer* SfLogger::g_startupTimer = new QElapsedTimer();
inline  SfLogger::LOGModles SfLogger::modle = SfLogger::LOGModle::fileOUT;
