//
// Created by 25137 on 25-9-27.
//

 #include "plotview.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QComboBox>
#include <QToolBar>

#include "plotmodel.h"
#include "plottree.h"
#include "plotcustom.h"
PlotView::PlotView(QWidget*parent)
	: QWidget(parent)
	,_graphView(new PlotCustom(this))
	,_treeView(new PlotTree(this))
	,_toolBar(new QToolBar(this))
	,_modleComboBox(new QComboBox(this))
	,_model(new PlotModel(this))
{
	initUI();
	initConnect();
}


void PlotView::initUI()
{
	auto splitter = new QSplitter(this);
	auto layout = new QVBoxLayout(this);

	_treeView->setModel(_model);

	_modleComboBox->addItems(QStringList()<<"单y轴" << "多y轴" << "多图表");
	_toolBar->addWidget(_modleComboBox);

	splitter->addWidget(_treeView);
	splitter->addWidget(_graphView);
	splitter->setSizes(QList<int>() << 280 << 800);

	layout->addWidget(_toolBar);
	layout->addWidget(splitter);

	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	_toolBar->setStyleSheet("QToolBar {\
		background - color: #fbfbfb;\
		border : 1px solid #fefefe;\
		}\
		QToolBar::separator{\
			width: 2px;\
			background - color:  #fbfbfb;\
		}");


	_treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void PlotView::initConnect()
{

}

void PlotView::add_plotData(const QSharedPointer<QCPGraphDataContainer> &data, QString plot_name) {

	_model->add_plotData(data,plot_name);
	_treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	_graphView->resetUI(_model);
}


