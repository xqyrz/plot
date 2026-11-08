//
// Created by 25137 on 2026/11/8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VisionConfigPage.h" resolved

#include "visionconfigpage.h"
#include "ui_VisionConfigPage.h"


VisionConfigPage::VisionConfigPage(QWidget* parent) : QWidget(parent), ui(new Ui::VisionConfigPage)
{
    ui->setupUi(this);
    new QVBoxLayout(ui->attribute);
}

VisionConfigPage::~VisionConfigPage() { delete ui; }
void VisionConfigPage::setIcon(QImage icon)
{
    ui->icon->setPixmap(QPixmap::fromImage(icon));
}
void VisionConfigPage::setTilt(QString tilt)
{
    ui->tilt->setText(tilt);
}
void VisionConfigPage::setType(QString type)
{
    ui->type->setText(type);
}
void VisionConfigPage::setDesc(QString desc)
{
    ui->desc->setText(desc);
}
void VisionConfigPage::setHelp(QString help)
{
    ui->help->setText(help);
}
void VisionConfigPage::setConfigPropertyItem(QWidget* w)
{
    w->setParent(ui->attribute);
    ui->attribute->layout()->addWidget(w);
}
void VisionConfigPage::showImage(QList<std::pair<QString, QImage>>& images)
{
    for (auto&var:images)
    {
        ui->imageView->loadImage(var.second,var.first);
    }
}
void VisionConfigPage::on_ok_clicked()
{
   emit okClicked();
    this->close();
}
void VisionConfigPage::on_cancel_clicked()
{
    this->close();
}
