//
// Created by 25137 on 2026/9/27.
//

#include "axfpage.h"
#include "axfmodel.h"
#include <QHeaderView>

AxfPage::AxfPage(QWidget* parent)
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
    header()->setStretchLastSection(false);
    setColumnWidth(0, 420);   // Name（文件路径/变量名）
    setColumnWidth(1, 220);   // Type
    setColumnWidth(2, 70);    // Size
    setColumnWidth(3, 100);   // Address
    setColumnWidth(4, 60);    // Select
    header()->setSectionResizeMode(0, QHeaderView::Stretch);
    header()->setSectionResizeMode(1, QHeaderView::Interactive);
    header()->setSectionResizeMode(2, QHeaderView::Fixed);
    header()->setSectionResizeMode(3, QHeaderView::Fixed);
    header()->setSectionResizeMode(4, QHeaderView::Fixed);

    m_model->setFile("F:/foc/V3.0/MOTOR/MDK-ARM/MOTOR/MOTOR.axf");

    // 默认展开一层：显示文件分组
    expandToDepth(1);
}

AxfPage::~AxfPage() {}
