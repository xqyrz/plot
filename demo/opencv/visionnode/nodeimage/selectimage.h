//
// Created by 25137 on 2026/11/8.
//

#ifndef PLOT_SELECTIMAGE_H
#define PLOT_SELECTIMAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class SelectImage;
}
QT_END_NAMESPACE

class SelectImage : public QWidget
{
    Q_OBJECT

public:
    explicit SelectImage(QWidget* parent = nullptr);
    ~SelectImage() override;
    void setFilePath(QString path);
    QString filePath()const;
signals:
    void imageChanged(QString path);
public slots:
    void on_selectBtn_clicked();
    void on_imagePath_textChanged(const QString& path);
private:
    Ui::SelectImage* ui;
};


#endif // PLOT_SELECTIMAGE_H
