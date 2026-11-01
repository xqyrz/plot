//
// Created by 25137 on 2026/10/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VisionApp.h" resolved

#include "visionapp.h"
#include "ui_VisionApp.h"

//#include "qimgv.h"

#include <QLabel>
#include <imageview.h>
VisionApp::VisionApp(QWidget* parent) : QWidget(parent), ui(new Ui::VisionApp)
{
    ui->setupUi(this);
    connect(ui->nodeEdit,&VisionCalPage::updateImage,this,[this](QList<std::pair<QString, QImage>> images)
    {
        ui->imageTab->clear();
    for(auto image:images)
    {
                // 1. 创建 QLabel
                QLabel *label = new QLabel(this);

                // 2. 将 QImage 转换为 QPixmap
                QPixmap pixmap = QPixmap::fromImage(image.second);

                // 3. 设置给 QLabel 显示
                label->setPixmap(pixmap);

                // 可选：让图片适应 Label 大小
                label->setScaledContents(true);
                ui->imageTab->addTab(label,image.first);
    }
        });
    ui->imageTab->clear();
    ui->imageTab->addTab(new ImageView() ,"");
}

VisionApp::~VisionApp() { delete ui; }
