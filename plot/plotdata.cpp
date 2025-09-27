//
// Created by x on 2025/9/24.
//

#include "plotdata.h"

PlotData::PlotData(QSharedPointer<QCPGraphDataContainer> data,QColor color,const QString &name, const QString &units,QObject *parent)
    :QObject(parent),_data(data),color(color),name(name),units(units){
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
