//
// Created by 25137 on 2026/9/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AxfPage.h" resolved

#include "axfUI.h"
#include "ui_AxfUI.h"

#include "axftree.h"
#include "axfmodel.h"
#include <QDebug>
AxfUI::AxfUI(QWidget* parent) :
QWidget(parent)
, ui(new Ui::AxfUI)
,m_tree(new AxfTree(this))
{
    ui->setupUi(this);
    layout()->addWidget(m_tree);
}

AxfUI::~AxfUI() { delete ui; }

void AxfUI::on_key_textChanged()
{
    if (ui->key->text().isEmpty()){
        m_tree->model()->setFilterText({});
    }
    m_tree->model()->setFilterText(ui->key->text().split(';'));
}
