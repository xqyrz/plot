//
// Created by 25137 on 2026/10/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VisionApp.h" resolved

#include "visionapp.h"
#include "ui_VisionApp.h"


VisionApp::VisionApp(QWidget* parent) : QWidget(parent), ui(new Ui::VisionApp) { ui->setupUi(this); }

VisionApp::~VisionApp() { delete ui; }
