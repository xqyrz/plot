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
    setWordWrap(true);
   // this->viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
   // this->viewport()->setAttribute(Qt::WA_NoSystemBackground);
   // this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // connect(BUS::interface(), &BUS::readIO_sig, model,
    //         [&](const QList<PLUG::Frame>& frames) { model->appendFrame(frames); });
    connect(model, &IoFrameModel::scrollToBottom, this, &IOView::scrollToBottom,Qt::UniqueConnection);

    QTimer::singleShot(1, this, [this]() { this->setModel(model); });

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&QWidget::customContextMenuRequested,this,[=](const QPoint& pos){
        QMenu menu(this);
       auto a =  menu.addAction(updateFlag()?"Stop":"Updata");
       auto action = menu.exec(mapToGlobal(pos));
        if (action ==a)
        {
           setUpdateFlag(!m_update);
            if (m_update)
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
void IOView::addRow(const PLUG::Frame& frame)
{
    model->appendFrame(frame);
}
IOView::~IOView()
{
    qInfo() << "IOView::~IOView()";
}


