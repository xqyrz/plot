//
// Created by 25137 on 26-4-12.
//

#ifndef DBM_H
#define DBM_H

#include <QObject>
#include "iocommon.h"
class QSqlDatabase;
class DBM : public QObject
{
    Q_OBJECT
public:
    static DBM* instance();
    bool addFrame(QString & ,QString & ,QString & ,QString & ,QString & ,QString & ,QByteArray&);
     bool addFrame (QList<IO::Frame>& frame);
    bool exportMemoryDb(const QString &filePath);
    QSqlDatabase* db(){return m_db;}
private:
    DBM(QSqlDatabase* db,QObject* parent = nullptr);
    ~DBM();


    private:
        QSqlDatabase* m_db;
};



#endif //DBM_H
