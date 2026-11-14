//
// Created by x on 2025/9/24.
//

#include "plotdata.h"

PlotData::PlotData(const uint64_t id, QSharedPointer<QCPGraphDataContainer> data, QColor color, const QString& name,
                   const QString& units, QObject* parent) :
    QObject(parent), id(id), _data(data), color(color), name(name), units(units)
{
}

double PlotData::getFreq() const
{
    if (_data.isNull()) {
        return -1;
    }
    if (_data->size()>2) {
        return _data->at(_data->size()-1)->key -_data->at(_data->size()-2)->key;
    }
    else {
        return -1;
    }
}
QString PlotData::getShowData() const {
    if (_data.isNull()) {
        return QString();
    }
    if (_data->size()) {
        return QString::number(_data->at(_data->size()-1)->value);
    }
    else {
        return QString();
    }
}

void PlotData::setVisible(bool flag) {
    if (flag != visible) {
        visible = flag;
        emit visibaleChanged(visible);
    }
}

bool PlotData::operator==(const PlotData &other) {
    if (other.getData()->isEmpty() || this->getData()->isEmpty()) {
        return false;
    }
    return other.getData() == this->getData();
}
void PlotData::clear()
{
    // 注意：QSharedPointer::clear() 只是把 _data 置空，并不会清空容器里的点。
    // 这里要清的是 QCPDataContainer 的内容，指针必须保留，否则：
    //   1) 曲线（QCPGraph 持有同一个容器的 shared_ptr）上的旧数据还在，删不干净；
    //   2) 之后 getData()->add(...) / getData()->isEmpty() 会空指针崩溃。
    if (_data) {
        _data->clear();
    }
}
