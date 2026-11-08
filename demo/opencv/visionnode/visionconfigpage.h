//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_VISIONCONFIGPAGE_H
#define PLOT_VISIONCONFIGPAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class VisionConfigPage;
}
QT_END_NAMESPACE

class VisionConfigPage : public QWidget
{
    Q_OBJECT

public:
    explicit VisionConfigPage(QWidget* parent = nullptr);
    ~VisionConfigPage() override;
    void setIcon(QImage icon);
    void setTilt(QString tilt);
    void setType(QString type);
    void setDesc(QString desc);
    void setHelp(QString help);

    void setConfigPropertyItem(QWidget* w);
    void showImage(QList<std::pair<QString,QImage>>&);
signals:
    void okClicked();
public slots:
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    Ui::VisionConfigPage* ui;
};


#endif // PLOT_VISIONCONFIGPAGE_H
