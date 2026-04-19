#include "IoFrameModel.h"
#include <QDebug>
#include <QColor>
using namespace IO;
IoFrameModel::IoFrameModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    // 初始化：预分配9999个空间，提升性能
    m_frames.reserve(9999);
    connect(&m_timer,&QTimer::timeout,this,[=]()
    {
        emit scrollToBottom();
    });
}

// ==================== 核心Model接口实现 ====================
int IoFrameModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return static_cast<int>(m_frames.size());
}

int IoFrameModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return cols.size();
}

QVariant IoFrameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_frames.size())
        return QVariant();

    const Frame &frame = m_frames[index.row()];
    const Config &cfg = frame.info;

    // 显示角色
    if (role == Qt::DisplayRole) {
        switch (cols.at(index.column())) {
        case COL_DEV:      return cfg.dev;
        case COL_CH:       return cfg.ch;
        case COL_OWN_DEV:  return cfg.own_dev;
        case COL_OWN_CH:   return cfg.own_ch;
        case COL_TR:       return frame.RT == IO::RT::RX?"RX":"TX";
        case COL_TIME:     return frame.time.toString("HH:mm:ss.zzz");
        case COL_DATA:     return QString::fromLatin1(frame.data.toHex(' ')).toUpper();; // 十六进制显示数据
        default:           return QVariant();
        }
    }
    else if (role == Qt::BackgroundRole)
    {
        // 示例1：根据【设备IP】设置不同背景色
        if (frame.RT == IO::RT::RX) {
            // 淡蓝色
            return QColor(240, 240, 240);
        }
        else  {
            // 淡绿色
            return QColor(220, 255, 220);
        }
    }
    // 对齐角色
    else if (role == Qt::TextAlignmentRole) {
        switch (cols.at(index.column())) {
        case COL_DATA:       return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        default:           return Qt::AlignCenter;
        }
        return Qt::AlignCenter;
    }

    return QVariant();
}
// ==================== 表头数据显示函数 ====================
// 功能：为 QTableView 提供水平/垂直表头的显示文本、样式等数据
// section：列号（水平表头）或行号（垂直表头）
// orientation：水平（列）还是垂直（行）
// role：要获取的数据角色（显示文本、对齐方式、颜色等）
QVariant IoFrameModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal ) {
        if (role == Qt::DisplayRole)
        {
            switch (cols.at(section)) {
            case COL_DEV:      return "设备IP";
            case COL_CH:       return "通道";
            case COL_OWN_DEV:  return "本机设备";
            case COL_OWN_CH:   return "本机通道";
            case COL_TIME:     return "时间";
            case COL_TR:       return "方向";
            case COL_DATA:     return "数据(HEX)";
            default:           return QVariant();
            }
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

// ==================== 数据插入：自动维护所有索引 ====================
void IoFrameModel::appendFrame(const Frame &frame)
{
    // 1. 获取即将插入的行号
    int newRow = static_cast<int>(m_frames.size());

    // 2. 通知Model开始插入行
    beginInsertRows(QModelIndex(), newRow, newRow);

    _addFrame(frame);
    // 5. 通知Model插入完成
    endInsertRows();
}

// ==================== 清空数据和索引 ====================
void IoFrameModel::clearAll()
{
    beginResetModel();
    m_frames.clear();
    m_indexByConfig.clear();
    m_indexByDev.clear();
    m_indexByCh.clear();
    m_indexByOwnDev.clear();
    m_indexByOwnCh.clear();
    endResetModel();
}

// ==================== 获取指定行数据 ====================
Frame IoFrameModel::getFrame(int row) const
{
    if (row >= 0 && row < m_frames.size())
        return m_frames[row];
    return Frame();
}

// ==================== 按条件查找：返回所有匹配的行号 ====================
const std::list<uint>* IoFrameModel::findRowsByConfig(const Config &cfg) const
{
    auto  devIndex= _indexOf(devs,cfg.dev);
    auto chIndex = _indexOf(chs,cfg.ch);
    auto ownDevIndex = _indexOf(own_devs,cfg.own_dev);
    auto ownChIndex = _indexOf(own_chs,cfg.own_ch);

    CfgId cfgId;
    cfgId.dev = devIndex;
    cfgId.ch = chIndex;
    cfgId.own_dev = ownDevIndex;
    cfgId.own_ch = ownChIndex;
    auto it = m_indexByConfig.find(qHash(cfg));
    if (it != m_indexByConfig.end())
        return &it->second;
    return nullptr;
}

 const std::list<uint>*  IoFrameModel::findRowsByDev(const QString &dev) const
{
    auto it = m_indexByDev.find(_indexOf(devs,dev));
    if (it != m_indexByDev.end())
        return &it->second;
    return nullptr;
}

const std::list<uint>* IoFrameModel::findRowsByChannel(const QString &ch) const
{
    auto it = m_indexByCh.find(_indexOf(chs,ch));
    if (it != m_indexByCh.end())
        return &it->second;
    return nullptr;
}

const std::list<uint>*  IoFrameModel::findRowsByOwnDev(const QString &ownDev) const
{
    auto it = m_indexByOwnDev.find(_indexOf(own_devs,ownDev));
    if (it != m_indexByOwnDev.end())
        return &it->second;
    return nullptr;
}

const std::list<uint>* IoFrameModel::findRowsByOwnCh(const QString& ownCh) const
{
    auto it = m_indexByOwnCh.find(_indexOf(own_chs,ownCh));
    if (it != m_indexByOwnCh.end())
        return &it->second;
    return nullptr;
}
void IoFrameModel::_addFrame(const IO::Frame& frame)
{
    m_frames.push_back(frame);
    auto  devIndex= indexOf(devs,frame.info.dev);
    auto chIndex = indexOf(chs,frame.info.ch);
    auto ownDevIndex = indexOf(own_devs,frame.info.own_dev);
    auto ownChIndex = indexOf(own_chs,frame.info.own_ch);

    CfgId cfgId;
    cfgId.dev = devIndex;
    cfgId.ch = chIndex;
    cfgId.own_dev = ownDevIndex;
    cfgId.own_ch = ownChIndex;
    auto row = m_frames.size() - 1;
    m_indexByConfig[cfgId.id].push_back(row);
    m_indexByDev[devIndex].push_back(row);
    m_indexByCh[chIndex].push_back(row);
    m_indexByOwnDev[ownDevIndex].push_back(row);
    m_indexByOwnCh[ownChIndex].push_back(row);
   if (!m_timer.isActive()) m_timer.start(10);
}
