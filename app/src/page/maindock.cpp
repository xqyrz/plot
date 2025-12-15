//
// Created by 25137 on 25-12-15.
//

#include "maindock.h"
#include "DockManager.h"
#include "DockAreaWidget.h"
#include "DockWidget.h"

#include <QWidgetAction>
#include <QComboBox>
#include <QLabel>
#include <QTableWidget>
#include <QInputDialog>
#include <QVBoxLayout>
using namespace  ads;
 MainDock::MainDock(QWidget *parent):QWidget(parent) {

	ads::CDockManager::setConfigFlag( ads::CDockManager::DockAreaHasCloseButton, false );
	ads::CDockManager::setConfigFlag( ads::CDockManager::AllTabsHaveCloseButton, true );
	ads::CDockManager::setConfigFlag( ads::CDockManager::DockAreaHasUndockButton, false );
	ads::CDockManager::setConfigFlag( ads::CDockManager::DockAreaDynamicTabsMenuButtonVisibility, true );
	ads::CDockManager::setConfigFlag( ads::CDockManager::DisableTabTextEliding, true );
	ads::CDockManager::setConfigFlag( ads::CDockManager::DoubleClickUndocksWidget, false );
    DockManager = new CDockManager(this);
	auto layout = new QVBoxLayout(this);
 	layout->addWidget(DockManager);
 	layout->setContentsMargins(0,0,0,0);
 	layout->setSpacing(0);
    // Set central widget
    auto* label = new QLabel();
    label->setText("This is a DockArea which is always visible, even if it does not contain any DockWidgets.");
    label->setAlignment(Qt::AlignCenter);
    CDockWidget* CentralDockWidget = DockManager->createDockWidget("CentralWidget");
    CentralDockWidget->setWidget(label);
    CentralDockWidget->setFeature(ads::CDockWidget::NoTab, true);
    auto* CentralDockArea = DockManager->setCentralWidget(CentralDockWidget);

    createPerspectiveUi();
}

void MainDock::closeEvent(QCloseEvent *event) {
 	DockManager->deleteLater();
	QWidget::closeEvent(event);
}

void MainDock::createPerspectiveUi() {
 	SavePerspectiveAction = new QAction("Create Perspective", this);
 	connect(SavePerspectiveAction, SIGNAL(triggered()), SLOT(savePerspective()));
 	PerspectiveListAction = new QWidgetAction(this);
 	PerspectiveComboBox = new QComboBox(this);
 	PerspectiveComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
 	PerspectiveComboBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
 	connect(PerspectiveComboBox, &QComboBox::textActivated,
		 DockManager, &CDockManager::openPerspective);
#else
 	connect(PerspectiveComboBox, SIGNAL(activated(const QString&)),
		 DockManager, SLOT(openPerspective(const QString&)));
#endif
 	PerspectiveListAction->setDefaultWidget(PerspectiveComboBox);
 	// ui->toolBar->addSeparator();
 	// ui->toolBar->addAction(PerspectiveListAction);
 	// ui->toolBar->addAction(SavePerspectiveAction);
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
