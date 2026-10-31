//
// Created by 25137 on 2026/10/31.
//

#ifndef PLOT_VISIONAPP_H
#define PLOT_VISIONAPP_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class VisionApp;
}
QT_END_NAMESPACE

class VisionApp : public QWidget
{
    Q_OBJECT

public:
    explicit VisionApp(QWidget* parent = nullptr);
    ~VisionApp() override;

private:
    Ui::VisionApp* ui;
};


#endif // PLOT_VISIONAPP_H
