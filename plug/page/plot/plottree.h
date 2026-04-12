//
// Created by x on 2025/9/24.
//

#ifndef PLOT_PLOTTREE_H
#define PLOT_PLOTTREE_H

#include <QTreeView>
#include "plotmodel.h"
class PlotTree:public QTreeView{
    Q_OBJECT
public:
    PlotTree(QWidget* parent=nullptr);
};


#endif //PLOT_PLOTTREE_H