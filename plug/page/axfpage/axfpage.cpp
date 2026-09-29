//
// Created by 25137 on 2026/9/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AxfPage.h" resolved

#include "axfpage.h"
#include "ui_AxfPage.h"

#include "axftree.h"
#include "axfmodel.h"
#include <QDebug>
AxfPage::AxfPage(QWidget* parent) :
QWidget(parent)
, ui(new Ui::AxfPage)
,m_tree(new AxfTree(this))
{
    ui->setupUi(this);
    layout()->addWidget(m_tree);
}

AxfPage::~AxfPage() { delete ui; }
void AxfPage::on_key_textChanged()
{
    if (ui->key->text().isEmpty()){
        m_tree->model()->setFilterText({});
    }
    m_tree->model()->setFilterText(ui->key->text().split(';'));
}
