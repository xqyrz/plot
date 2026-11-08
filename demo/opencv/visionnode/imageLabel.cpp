//
// Created by 25137 on 2026/10/31.
//

#include <QFileDialog>
#include "imageLabel.h"

void ImageLabel::slecetImagePath(const QString &path) {
    // 打开单个文件
    QString m_path = QFileDialog::getOpenFileName(
        this,                       // 父窗口
        "选择文件",                 // 标题
        path,           // 默认目录（可用记住的上次路径）
        ";图片 (*.png *.jpg *.bmp)"  // 过滤，分号分隔多组
    );
    if (!m_path.isEmpty()) {
        setImagePath(m_path);
    }
}

void ImageLabel::setImagePath(const QString &path) {
    QFileInfo fileInfo(path);
    m_imagePath = path;
    setText(fileInfo.fileName());
}