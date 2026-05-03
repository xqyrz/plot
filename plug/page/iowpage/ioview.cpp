//
// Created by 25137 on 26-4-12.
//

#include "ioview.h"
#include <QDebug>
#include <QHeaderView>
#include <QList>
#include <QTimer>
#include <QtSql/QSqlTableModel>
//#include "bus/bus.h"

IOView* IOView::instance(QWidget* parent)
{
    static IOView* instance=new IOView(parent);
    return instance;
}
IOView::IOView(QWidget* parent) : QTableView(parent), model(new IoFrameModel(this))
{
    // connect(BUS::interface(), &BUS::readIO_sig, model,
    //         [&](const QList<IO::Frame>& frames) { model->appendFrame(frames); });
    connect(model, &IoFrameModel::scrollToBottom, this, &IOView::scrollToBottom);
    setContextMenuPolicy(Qt::CustomContextMenu);
    QTimer::singleShot(1, this, [this]() { this->setModel(model); });
}
void IOView::addRow(const IO::Frame& frame)
{
    model->appendFrame(frame);
}
IOView::~IOView()
{
    qInfo() << "IOView::~IOView()";
}


