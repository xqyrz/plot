//
// Created by 25137 on 26-4-12.
//

#include "dbm.h"
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
static DBM* instance = nullptr;
static QSqlDatabase* _db()
{
    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError().text();
    }
    QSqlQuery query;

    // 2. 创建表
    if (!query.exec(R"(
            CREATE TABLE data_stream (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            time_str TEXT NOT NULL,
            channel TEXT NOT NULL,
            frame_id TEXT NOT NULL,
            period INTEGER,
            frame_count INTEGER,
            direction TEXT,
            length INTEGER,
            data_hex TEXT,
            data_utf8 TEXT
            );
           )")) {
        qWarning() << "Error:" << query.lastError().text();
    }
    return &db;
}
DBM* DBM::instance()
{
    static DBM _instance(_db());
    return &_instance;
}
inline DBM::DBM(QSqlDatabase* __db, QObject* parent) : QObject(parent), m_db(__db)
{

}
DBM::~DBM()
{
   // QObject::~QObject();
}

bool DBM::addFrame(QString& time, QString& channel, QString& frame_id, QString& period, QString& frame_count,
                   QString& direction, QByteArray& data)
{
    QSqlQuery query(*m_db);

    // 1. 开启事务
    if (!m_db->transaction())
    {
        qWarning() << "Transaction start failed:" << m_db->lastError().text();
        return false;
    }

    // 2. 准备 SQL
    query.prepare(R"(
        INSERT INTO data_stream
        (time_str, channel, frame_id, period, frame_count,
         direction, length, data_hex, data_utf8)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
    )");

    // 3. 循环插入
    query.addBindValue(time);
    query.addBindValue(channel);
    query.addBindValue(frame_id);
    query.addBindValue(period);
    query.addBindValue(frame_count);
    query.addBindValue(direction);
    query.addBindValue(data.size());
    query.addBindValue(data.toHex(' '));
    query.addBindValue(QString::fromUtf8(data));

    if (!query.exec())
    {
        qWarning() << "Insert failed:" << query.lastError().text();
        m_db->rollback();
        return false;
    }

    query.clear(); // 关键：清理 bind，避免累积
    query.prepare(R"(
         INSERT INTO data_stream
         (time_str, channel, frame_id, period, frame_count,
          direction, length, data_hex, data_utf8)
          VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
       )");


    // 4. 提交事务
    if (!m_db->commit())
    {
        qWarning() << "Commit failed:" << m_db->lastError().text();
        m_db->rollback();
        return false;
    }

    return true;
}


bool DBM::addFrame(QList<IO::Frame>& frames)
{
    QSqlQuery query(*m_db);

    // 1. 开启事务
    if (!m_db->transaction())
    {
        qWarning() << "Transaction start failed:" << m_db->lastError().text();
        return false;
    }

    // 2. 准备 SQL
    query.prepare(R"(
        INSERT INTO data_stream
        (time_str, channel, frame_id, period, frame_count,
         direction, length, data_hex, data_utf8)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
    )");
    for (const auto &frame : frames)
    {
        // 3. 循环插入
        query.addBindValue(frame.time.toString("HH:mm:ss.zzz"));
        query.addBindValue(frame.info.dev);
        query.addBindValue(frame.info.ch);
        query.addBindValue("");
        query.addBindValue("");
        query.addBindValue(frame.info.own_ch);
        query.addBindValue(frame.data.size());
        query.addBindValue(frame.data.toHex(' '));
        query.addBindValue(QString::fromUtf8(frame.data));

        if (!query.exec())
        {
            qWarning() << "Insert failed:" << query.lastError().text();
            m_db->rollback();
            return false;
        }

        query.clear(); // 关键：清理 bind，避免累积
        query.prepare(R"(
         INSERT INTO data_stream
         (time_str, channel, frame_id, period, frame_count,
          direction, length, data_hex, data_utf8)
          VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
       )");
    }

    // 4. 提交事务
    if (!m_db->commit())
    {
        qWarning() << "Commit failed:" << m_db->lastError().text();
        m_db->rollback();
        return false;
    }

    return true;
}


bool DBM::exportMemoryDb(const QString &filePath)
{
    QSqlQuery query(*m_db);

    // 1. 附加磁盘数据库
    if (!query.exec(QString("ATTACH DATABASE '%1' AS disk").arg(filePath))) {
        qWarning() << query.lastError();
        return false;
    }

    // 2. 创建表并拷贝数据
    if (!query.exec(R"(
        CREATE TABLE disk.data_stream AS
        SELECT * FROM main.data_stream
    )")) {
        qWarning() << query.lastError();
        return false;
    }

    // 3. 断开附加
    query.exec("DETACH DATABASE disk");

    return true;
}