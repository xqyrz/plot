//
// Created by 25137 on 2026/10/31.
//

#ifndef PLOT_IMAGELINEEDIT_H
#define PLOT_IMAGELINEEDIT_H

#include <QtWidgets/QLabel>

class ImageLabel:public QLabel
{
    Q_OBJECT
public:
    ImageLabel(QWidget* parent = nullptr):QLabel(parent){};

    void slecetImagePath(const QString &path);
    void setImagePath(const QString &path);
    QString path() const { return m_imagePath; }
signals:
    void textChanged(QString const &text);
private:
    QString m_imagePath;
};


#endif // PLOT_IMAGELINEEDIT_H
