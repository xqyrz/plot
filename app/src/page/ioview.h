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
    IOView(QWidget* parent = nullptr);
private:

    IoFrameModel* model;
};



#endif //IOLISTVIEW_H
