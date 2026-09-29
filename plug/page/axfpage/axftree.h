//
// Created by 25137 on 2026/9/27.
//

#ifndef PLOT_AXFTREE_H
#define PLOT_AXFTREE_H

#include <QTreeView>
class AxfModel;
class AxfTree:public QTreeView
{
    Q_OBJECT
public:
    AxfTree(QWidget* parent = nullptr);
    ~AxfTree();
    AxfModel* model() const { return m_model; }
private:
    AxfModel* m_model;
};


#endif // PLOT_AXFTREE_H
