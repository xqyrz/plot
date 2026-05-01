//
// Created by 25137 on 26-4-12.
//

#ifndef IOLISTVIEW_H
#define IOLISTVIEW_H


#include <QTableView>
class IoFrameModel;
class IOView:public QTableView {
Q_OBJECT
public:
    static IOView* instance(QWidget* parent = nullptr);
private:
    IOView(QWidget* parent = nullptr);
    ~IOView();
    IoFrameModel* model;
};



#endif //IOLISTVIEW_H
