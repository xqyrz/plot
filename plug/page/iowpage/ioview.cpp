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
#include <QMenu>
IOView* IOView::instance(QWidget* parent)
{
    static IOView* instance=new IOView(parent);
    return instance;
}
IOView::IOView(QWidget* parent) : QTableView(parent), model(new IoFrameModel(this))
{

   // this->viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
   // this->viewport()->setAttribute(Qt::WA_NoSystemBackground);
   // this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // connect(BUS::interface(), &BUS::readIO_sig, model,
    //         [&](const QList<IO::Frame>& frames) { model->appendFrame(frames); });
    connect(model, &IoFrameModel::scrollToBottom, this, &IOView::scrollToBottom,Qt::UniqueConnection);

    QTimer::singleShot(1, this, [this]() { this->setModel(model); });

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&QWidget::customContextMenuRequested,this,[=](const QPoint& pos){
        QMenu menu(this);
       auto Updata =  menu.addAction(update?"Stop":"Updata");
       auto action = menu.exec(mapToGlobal(pos));
        if (action ==Updata)
        {
            update =!update;
            if (update)
            {
                connect(model, &IoFrameModel::scrollToBottom, this, &IOView::scrollToBottom,Qt::UniqueConnection);
            }
            else
            {
                disconnect(model, &IoFrameModel::scrollToBottom, this, &IOView::scrollToBottom);
            }
        }
    });

}
void IOView::addRow(const IO::Frame& frame)
{
    model->appendFrame(frame);
}
IOView::~IOView()
{
    qInfo() << "IOView::~IOView()";
}


