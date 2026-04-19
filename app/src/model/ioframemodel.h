#ifndef IOFRAMEMODEL_H
#define IOFRAMEMODEL_H

#include <QAbstractTableModel>
#include <QDateTime>
#include <QByteArray>
#include <QString>
#include <vector>
#include <map>
#include <list>
#include <QHash>
#include <QTimer>
#include "iocommon.h"
// 自定义哈希函数（用于map的key）
inline uint qHash(const IO::Config &key, uint seed = 0)
{
    return qHash(key.dev, seed)
            ^ qHash(key.ch, seed)
            ^ qHash(key.own_dev, seed)
            ^ qHash(key.own_ch, seed);
}

class IoFrameModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    static int _indexOf( const std::vector<QString>& v, const QString& value)
    {
        auto it = std::find(v.begin(), v.end(), value);
        if (it == v.end())
        {
            return -1;
        }
        return std::distance(v.begin(), it);
    }
    static int indexOf(  std::vector<QString>& v, const QString& value)
    {
        auto id = _indexOf(v, value);
        if (id<0)
        {
            v.push_back(value);
            return v.size() - 1;
        }
        else return id;
    }
    explicit IoFrameModel(QObject *parent = nullptr);

    // ==================== 必须实现的 Model 核心接口 ====================
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // ==================== 数据操作接口（对外提供） ====================
    // 插入一帧数据
    void appendFrame(const IO::Frame &frame);
    template<typename T>
    void appendFrame(const T& frames)
    {
        if (frames.empty()) return;

        int start = static_cast<int>(m_frames.size());
        int count = static_cast<int>(frames.size());
        int end = start + count - 1;

        beginInsertRows(QModelIndex(), start, end);

        for (const auto& frame : frames)
        {
            _addFrame(frame);
        }

        endInsertRows();
    }
    // 清空所有数据和索引
    void clearAll();
    // 获取指定行的数据
    IO::Frame getFrame(int row) const;

    // ==================== 按条件查找接口（基于map索引） ====================
    // 1. 按完整Config查找所有行号
    const std::list<uint>* findRowsByConfig(const IO::Config &cfg) const;
    // 2. 按设备IP(dev)查找所有行号
    const std::list<uint>* findRowsByDev(const QString &dev) const;
    // 3. 按通道(ch)查找所有行号
    const std::list<uint>* findRowsByChannel(const QString &ch) const;
    // 4. 按本机设备(own_dev)查找所有行号
    const std::list<uint>* findRowsByOwnDev(const QString &ownDev) const;
    // 5. 按本机通道(own_ch)查找所有行号
    const std::list<uint>* findRowsByOwnCh(const QString &ownCh) const;
signals:
    void scrollToBottom();
private:
    void _addFrame(const IO::Frame& frame);
    typedef struct
    {
        union
        {
            uint16_t dev;//设备 ip
            uint16_t ch;//通道
            uint16_t own_dev; //自己
            uint16_t own_ch;
        };
        uint64_t id;
    }CfgId;
    std::vector<QString> devs;
    std::vector<QString> chs;
    std::vector<QString> own_devs;
    std::vector<QString> own_chs;
    const std::vector<QString> rt{"RX","TX"};
    // 数据存储：预分配9999空间
    std::vector<IO::Frame> m_frames;

    // ==================== 多级分类索引（核心） ====================
    // 1. 完整Config哈希 -> 数据行号列表
    std::map<uint64_t, std::list<uint>> m_indexByConfig;
    // 2. 设备IP(dev)哈希 -> 数据行号列表
    std::map<uint, std::list<uint>> m_indexByDev;
    // 3. 通道(ch)哈希 -> 数据行号列表
    std::map<uint, std::list<uint>> m_indexByCh;
    // 4. 本机设备(own_dev)哈希 -> 数据行号列表
    std::map<uint, std::list<uint>> m_indexByOwnDev;
    // 5. 本机通道(own_ch)哈希 -> 数据行号列表
    std::map<uint, std::list<uint>> m_indexByOwnCh;
    // 5. 本机通道(own_ch)哈希 -> 数据方向
    std::map<uint, std::list<uint>> m_indexByRT;
    // 列枚举（便于维护）
    enum Column {
        COL_TIME=0,          // 时间戳
        COL_DEV ,       // 设备IP
        COL_CH,            // 通道
        COL_OWN_DEV,       // 本机设备
        COL_OWN_CH,        // 本机通道

        COL_TR,            // 数据方向
        COL_DATA,          // 数据内容
        COL_COUNT,          // 总列数
    };
    QList<Column> cols={
        COL_TIME,          // 时间戳
        COL_DEV,       // 设备IP
        COL_CH,            // 通道
        COL_OWN_DEV,       // 本机设备
        COL_OWN_CH,        // 本机通道

        COL_TR,            // 数据方向
        COL_DATA,          // 数据内容
     };
    QTimer m_timer;
};

#endif // IOFRAMEMODEL_H