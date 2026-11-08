//
// Created by 25137 on 2026/11/8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SelectImage.h" resolved

#include "selectimage.h"
#include "ui_SelectImage.h"

#include <QFileDialog>
SelectImage::SelectImage(QWidget* parent) : QWidget(parent), ui(new Ui::SelectImage) { ui->setupUi(this); }

SelectImage::~SelectImage() { delete ui; }
void SelectImage::setFilePath(QString m_path)
{
    ui->imagePath->setText(m_path);
}
QString SelectImage::filePath() const
{
    return  ui->imagePath->text();
}
void SelectImage::on_selectBtn_clicked()
{
    QString m_path = QFileDialog::getOpenFileName(
    this,                       // 父窗口
    "选择文件",                 // 标题
    ui->imagePath->text(),           // 默认目录（可用记住的上次路径）
    ";图片 (*.png *.jpg *.bmp)"  // 过滤，分号分隔多组
);
    if (!m_path.isEmpty()) {
        ui->imagePath->setText(m_path);
    }
}
void SelectImage::on_imagePath_textChanged(const QString& path)
{
    Q_EMIT imageChanged(path);
}
