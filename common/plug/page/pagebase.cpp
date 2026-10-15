//
// Created by 25137 on 26-2-10.
//

#include "pagebase.h"
#include <QWidget>

PageBase::PageBase(QWidget* parent):InterfaceBase(parent),m_ui(new QWidget())
{
    m_ui->setParent(parent);
}
PageBase::~PageBase()
{
    m_ui->deleteLater();
}
