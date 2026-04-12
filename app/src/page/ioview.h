//
// Created by 25137 on 26-4-12.
//

#ifndef IOLISTVIEW_H
#define IOLISTVIEW_H


#include <QTableView>
class QSqlTableModel;
class IOView:public QTableView {
Q_OBJECT
public:
    IOView(QWidget* parent = nullptr);
    void init();
private:

    QSqlTableModel* model;
};



#endif //IOLISTVIEW_H
