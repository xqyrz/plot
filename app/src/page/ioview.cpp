//
// Created by 25137 on 26-4-12.
//

#include "ioview.h"
#include <QtSql/QSqlTableModel>
#include  "db/dbm.h"
#include <QSqlError>
#include <QDebug>
#include <QHeaderView>
#include <QTimer>
#include <QList>
#include "model/ioframemodel.h"
#include "bus/bus.h"
IOView::IOView(QWidget* parent) : QTableView(parent)
, model(new IoFrameModel(this))
{
    connect(BUS::interface(),&BUS::readIO_sig,model,[&](const QList<IO::Frame>& frames)
    {
        model->appendFrame(frames);
    });
    connect(model,&IoFrameModel::scrollToBottom,this,&IOView::scrollToBottom);
    setContextMenuPolicy(Qt::CustomContextMenu);
    QTimer::singleShot(1,this,[this](){
        this->setModel(model);
    });

}


