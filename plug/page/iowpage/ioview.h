//
// Created by 25137 on 26-4-12.
//

#ifndef IOLISTVIEW_H
#define IOLISTVIEW_H


#include <QTableView>
#include "ioframemodel.h"
class IoFrameModel;
class IOView:public QTableView {
Q_OBJECT
public:
    static IOView* instance(QWidget* parent = nullptr);
    IOView(QWidget* parent = nullptr);
public:
    void addRow(const IO::Frame& frame);
private:

    ~IOView();
    IoFrameModel* model;
};



#endif //IOLISTVIEW_H
