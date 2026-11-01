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

    for(auto image:images)
    {
        ui->imageView->loadImage(image.second,image.first);
    }
        });

}

VisionApp::~VisionApp() { delete ui; }
