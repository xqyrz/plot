//
// Created by 25137 on 26-4-12.
//

#include "ioview.h"
#include <QtSql/QSqlTableModel>
#include  "db/dbm.h"
#include <QSqlError>
#include <QDebug>
#include <QHeaderView>
IOView::IOView(QWidget* parent) : QTableView(parent), model(new QSqlTableModel(this,*(DBM::instance()->db())))
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&IOView::customContextMenuRequested,this,[=]()
    {
        model->select();
    });


}
void IOView::init()
{
    auto dbm = DBM::instance();
    QByteArray d(61, 61);
    QString time("time");
    QString channel("channel");
    QString frame_id("frame_id");
    QString period("period");
    QString frame_cout("frame_cout");
    QString dir("dir");
    dbm->addFrame(time, channel, frame_id, period, frame_cout, dir, d);
    model->setTable("data_stream");
    // 设置编辑策略：手动提交修改（也可改为OnFieldChange自动提交）
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // 读取数据
    model->select();

    // 设置表头中文名称（适配你的表字段）
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "时间");
    model->setHeaderData(2, Qt::Horizontal, "通道");
    model->setHeaderData(3, Qt::Horizontal, "帧ID");
    model->setHeaderData(4, Qt::Horizontal, "周期");
    model->setHeaderData(5, Qt::Horizontal, "帧计数");
    model->setHeaderData(6, Qt::Horizontal, "方向");
    model->setHeaderData(7, Qt::Horizontal, "长度");
    model->setHeaderData(8, Qt::Horizontal, "十六进制数据");
    model->setHeaderData(9, Qt::Horizontal, "UTF8数据");

    this->setModel(model);
    // 列宽自适应内容
    horizontalHeader()->setStretchLastSection(true);
    //horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // 禁止编辑（可选，移除即可支持编辑）
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 选中整行
    setSelectionBehavior(QAbstractItemView::SelectRows);
    DBM::instance()->exportMemoryDb("iostream.db");
}

