//
// Created by 25137 on 25-12-15.
//

#ifndef MAINDOCK_H
#define MAINDOCK_H

#include <QWidget>
class QWidgetAction;
class QComboBox;
namespace ads {
    class CDockManager;
    class CDockAreaWidget;
    class CDockWidget;
};
class MainDock:public QWidget{
Q_OBJECT
    public:
    explicit MainDock(QWidget*parent = nullptr);
protected:
    void closeEvent(QCloseEvent* event) override;

private:
    QAction* SavePerspectiveAction = nullptr;
    QWidgetAction* PerspectiveListAction = nullptr;
    QComboBox* PerspectiveComboBox = nullptr;

    ads::CDockManager* DockManager;
    ads::CDockAreaWidget* StatusDockArea{};
    ads::CDockWidget* TimelineDockWidget{};

    void createPerspectiveUi();

private slots:
    void savePerspective();
};




#endif //MAINDOCK_H
