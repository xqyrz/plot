//
// Created by 25137 on 2026/10/11.
//

#include "axfpage.h"
#include "AxfUI.h"
AxfPage::AxfPage(QWidget* parent):
    PageBase(parent)
{
    ui()->deleteLater();
    m_ui = new AxfUI(parent);
    m_inputPorts << PLUG::InputType::IN_IO_TX;
}
