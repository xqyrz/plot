//
// Created by 25137 on 2026/9/27.
//

#include "axftree.h"
#include <QHeaderView>
#include "axfmodel.h"

AxfTree::AxfTree(QWidget* parent)
    : QTreeView(parent)
    , m_model(new AxfModel(this))
{
    setModel(m_model);

    setUniformRowHeights(true);
    setAllColumnsShowFocus(true);
    setRootIsDecorated(true);
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    // 表头：Select 列固定大小，其余自适应
    //header()->setStretchLastSection(false);

    m_model->setFile("F:/foc/V3.0/MOTOR/MDK-ARM/MOTOR/MOTOR.axf");

    // 默认展开一层：显示文件分组
   // expandToDepth(1);


    // 构造函数中绑定信号
    connect(this, &QTreeView::doubleClicked, this, [&](const QModelIndex &index)
    {
        if (!index.isValid()) return;

        QVariant stateVar = m_model->data(index, Qt::CheckStateRole);
        Qt::CheckState state = static_cast<Qt::CheckState>(stateVar.toInt());

        // 翻转勾选状态
        Qt::CheckState newState = (state == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
        m_model->setData(index, newState, Qt::CheckStateRole);
    });
}

AxfTree::~AxfTree() {}
