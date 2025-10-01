//
// Created by 25137 on 25-9-27.
//

 #include "plotview.h"
#include <QSettings>
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
	QSettings settings(PLOT::PLOT_COMPANY,PLOT::PLOT_PRODUCT);
	plotType =(PLOT::PlotType)settings.value("plotType",PLOT::TYPE_oneXoneY).toInt();
	initUI();
	initConnect();
}

void PlotView::expandAll() const {
	_treeView->expandAll();
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
	splitter->setSizes(QList<int>() << 200 << 1800);

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
	_modleComboBox->setCurrentIndex(plotType);

}

void PlotView::initConnect()
{
	connect(_modleComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this, &PlotView::setPlotType);
	connect(this, &PlotView::plotTypeChanged, _graphView, &PlotCustom::setPlotType);
	//connect(_graphView,&PlotCustom::pressedPlot,_treeView,&PlotTree::set)
	connect(_model, &QAbstractItemModel::dataChanged, this,[=]() {
		_graphView->resetUI();
	});
}

void PlotView::add_plotData(const QSharedPointer<QCPGraphDataContainer> &data, QString plot_name) {

	_model->add_plotData(data,plot_name);
	_treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	_graphView->resetUI(_model);
}

void PlotView::setCurrentPlot(int type, const QCPLayerable *item) {
	switch (type) {
		case PLOT::ITEM_AXIS:
			break;
		case PLOT::ITEM_GRAPH:
			break;
		default:qWarning("PlotView::setCurrentPlot: unknown type");
			break;
	}
}

void PlotView::setPlotType(int type) {
	if (type != plotType) {
		plotType = type;
		emit plotTypeChanged(plotType);
	}
}


