//
// Created by 25137 on 2026/9/27.
//

#ifndef PLOT_AXFPAGE_H
#define PLOT_AXFPAGE_H

#include <QTreeView>
class AxfModel;
class AxfPage:public QTreeView
{
    Q_OBJECT
public:
    AxfPage(QWidget* parent = nullptr);
    ~AxfPage();
private:
    AxfModel* m_model;
};


#endif // PLOT_AXFPAGE_H
