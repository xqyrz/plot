//
// Created by 25137 on 2026/11/14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Gamma.h" resolved

#include "gamma.h"
#include "ui_Gamma.h"
#include "plotview.h"

Gamma::Gamma(QWidget* parent) : QWidget(parent)
, ui(new Ui::Gamma)
, plotView(new PlotView(this))
{
    ui->setupUi(this);
}

Gamma::~Gamma() { delete ui; }
