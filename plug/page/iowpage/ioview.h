//
// Created by 25137 on 26-4-12.
//

#ifndef IOLISTVIEW_H
#define IOLISTVIEW_H


#include <QTableView>
#include "ioframemodel.h"
class IoFrameModel;
class IOInterface;
class IOView:public QTableView {
Q_OBJECT
    Q_PROPERTY(bool updateFlag READ updateFlag WRITE setUpdateFlag NOTIFY updateFlagChanged)
public:
    static IOView* instance(QWidget* parent = nullptr);
    IOView(QWidget* parent = nullptr);
public:
    void addRow(const INC::Frame& frame);
    bool updateFlag() const{return m_update;};
public slots:
    void setUpdateFlag(bool flag){m_update = flag;emit updateFlagChanged(m_update);};
signals:
    void updateFlagChanged(bool update);
private:

    ~IOView();
    IoFrameModel* model;

    bool m_update =true;
    QList<IOInterface*> ios;
};



#endif //IOLISTVIEW_H
