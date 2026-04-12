//
// Created by 25137 on 26-4-12.
//

#ifndef DBM_H
#define DBM_H

#include <QObject>
class QSqlDatabase;
class DBM : public QObject
{
    Q_OBJECT
public:
    static DBM* instance();
    bool addFrame(QString & ,QString & ,QString & ,QString & ,QString & ,QString & ,QByteArray&);
    bool exportMemoryDb(const QString &filePath);
private:
    DBM(QSqlDatabase* db,QObject* parent = nullptr);
    ~DBM();


    private:
        QSqlDatabase* db;
};



#endif //DBM_H
