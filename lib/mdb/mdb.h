//
// Created by 25137 on 26-6-1.
//

#ifndef MDB_H
#define MDB_H

#include <QString>
#include <QMutexLocker>
#include <QVariant>
#ifdef MDB_LIBRARY
#define MDB_EXPORT Q_DECL_EXPORT
#else
#define MDB_EXPORT Q_DECL_IMPORT
#endif
class MDB_EXPORT MDB
{
public:
    static MDB* instance();

    void add(
        const QString& key,
        const QVariant& value)
    {
        QMutexLocker locker(&mutex);

        map[key].append(value);
    }
    QList<QVariant> get(const QString& key)const
    {
        if (map.contains(key))
        {
            return map.value(key);
        }
        else
        {
            return {};
        }
    }
private:
    MDB() = default;
    ~MDB() = default;

    MDB(const MDB&) = delete;
    MDB& operator=(const MDB&) = delete;

    QMutex mutex;
    QMap<QString, QList<QVariant>> map;
};



#endif //MDB_H
