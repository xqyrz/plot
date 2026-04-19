//
// Created by 25137 on 25-12-15.
//

#include "maindock.h"
#include <QComboBox>
#include <QInputDialog>
#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidgetAction>
#include "DockAreaWidget.h"
#include "DockManager.h"
#include "DockWidget.h"
#include "ioview.h"
#include "plotview.h"


#include "nodeeditpage.h"
using namespace  ads;
 MainDock::MainDock(QWidget *parent):
QWidget(parent)
,ioView(new IOView(this))
{
 	setObjectName("mainDock");
	ads::CDockManager::setConfigFlag( ads::CDockManager::DockAreaHasCloseButton, false );
	ads::CDockManager::setConfigFlag( ads::CDockManager::AllTabsHaveCloseButton, true );
	ads::CDockManager::setConfigFlag( ads::CDockManager::DockAreaHasUndockButton, false );
	ads::CDockManager::setConfigFlag( ads::CDockManager::DockAreaDynamicTabsMenuButtonVisibility, true );
	ads::CDockManager::setConfigFlag( ads::CDockManager::DisableTabTextEliding, true );
	ads::CDockManager::setConfigFlag( ads::CDockManager::DoubleClickUndocksWidget, false );
    DockManager = new CDockManager(this);
 	//让 QSS 生效的 唯一可靠做法

	auto layout = new QVBoxLayout(this);
 	layout->addWidget(DockManager);
 	layout->setContentsMargins(0,0,0,0);
 	layout->setSpacing(0);
    //Set central widget
     _InitPage();

}

void MainDock::closeEvent(QCloseEvent *event) {
 	DockManager->deleteLater();
	QWidget::closeEvent(event);
}

void MainDock::createPerspectiveUi()
{
    SavePerspectiveAction = new QAction("Create Perspective", this);
    connect(SavePerspectiveAction, SIGNAL(triggered()), SLOT(savePerspective()));
    PerspectiveListAction = new QWidgetAction(this);
    PerspectiveComboBox = new QComboBox(this);
    PerspectiveComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    PerspectiveComboBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    connect(PerspectiveComboBox, &QComboBox::textActivated, DockManager, &CDockManager::openPerspective);
#else
    connect(PerspectiveComboBox, SIGNAL(activated(const QString&)), DockManager, SLOT(openPerspective(const QString&)));
#endif
    PerspectiveListAction->setDefaultWidget(PerspectiveComboBox);
    // ui->toolBar->addSeparator();
    // ui->toolBar->addAction(PerspectiveListAction);
    // ui->toolBar->addAction(SavePerspectiveAction);
}
void MainDock::_InitPage()
{
     QWidget* w = new NodeEditPage(this);
    auto pre =  _addDock(w,"node");
     w = PlotView::instance(this);
    _addDock(w,"plot",pre);
     _addDock(ioView,"iostream",pre);

    pre->setCurrentDockWidget(pre->dockWidget(0));
}
ads::CDockAreaWidget* MainDock::_addDock(QWidget* widget, QString name,ads::CDockAreaWidget* parent)
 {
     widget->setObjectName(name);
     auto dockWidget = DockManager->createDockWidget(name);
     dockWidget->setWidget(widget);
     dockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
     dockWidget->setMinimumSize(200, 150);

     return DockManager->addDockWidget(ads::CenterDockWidgetArea, dockWidget,parent);
 }

void MainDock::savePerspective() {
 	QString PerspectiveName = QInputDialog::getText(this, "Save Perspective", "Enter unique name:");
 	if (PerspectiveName.isEmpty())
 	{
 		return;
 	}

 	DockManager->addPerspective(PerspectiveName);
 	QSignalBlocker Blocker(PerspectiveComboBox);
 	PerspectiveComboBox->clear();
 	PerspectiveComboBox->addItems(DockManager->perspectiveNames());
 	PerspectiveComboBox->setCurrentText(PerspectiveName);
}
