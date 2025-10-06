//
// Created by 25137 on 25-9-27.
//

 #include "plotview.h"
#include <QSettings>
#include <QSplitter>
#include <QVBoxLayout>
#include <QComboBox>
#include <QToolBar>


#include "plottree.h"
#include "plotcustom.h"
PlotView::PlotView(QWidget*parent)
	: QWidget(parent)
	,zero(QDateTime::currentDateTime().toMSecsSinceEpoch())
	,_graphView(new PlotCustom(this))
	,_treeView(new PlotTree(this))
	,_toolBar(new QToolBar(this))
	,_modleComboBox(new QComboBox(this))
	,_xSpinBox(new QSpinBox(this))
    ,_xCheckBox(new QCheckBox(this))
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

//TODO:严重性能问题，但是这个实现动态信号显示，静态可以优化


void PlotView::initUI()
{
	auto splitter = new QSplitter(this);
	auto layout = new QVBoxLayout(this);

	_treeView->setModel(_model);

	_modleComboBox->addItems(QStringList()<<"单y轴" << "多y轴" << "多图表");

	_xCheckBox->setText("采样区间");
	_xCheckBox->setChecked(true);

	_xSpinBox->setRange(1,99999999);
	_xSpinBox->setValue(100);

	_toolBar->addWidget(_modleComboBox);
	_toolBar->addWidget(_xCheckBox);
	_toolBar->addWidget(_xSpinBox);

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
	_graphView->setXInterval(_xSpinBox->value());
	_graphView->setXCheckBox(_xCheckBox->isChecked());
}

void PlotView::initConnect()
{
	connect(_modleComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this, &PlotView::setPlotType);

	connect(_xSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),_graphView, &PlotCustom::setXInterval);
	connect(_xCheckBox,QOverload<int>::of(&QCheckBox::stateChanged),_graphView, &PlotCustom::setXCheckBox);

	connect(this, &PlotView::plotTypeChanged, _graphView, &PlotCustom::setPlotType);
	//connect(_graphView,&PlotCustom::pressedPlot,_treeView,&PlotTree::set)
	connect(_model, &QAbstractItemModel::dataChanged, this,[this]() {
		_graphView->resetUI();
	});

}

void PlotView::addSignalData(const QList<IOAPP::SIGNALS> &_signals) {
	{
		for (const auto &s : _signals) {
			auto node = _model->getNode(s.id);
			if (!node) {
				auto d = QSharedPointer<QCPGraphDataContainer>::create();
				QMetaObject::invokeMethod(
						this,
						"add_plotData", // 必须是 QObject slots 函数
						Qt::BlockingQueuedConnection, // 阻塞等待执行完成
						Q_ARG(uint64_t, s.id),
						Q_ARG(QSharedPointer<QCPGraphDataContainer>&, d),
						Q_ARG(QString, QString::fromStdString(s.name))
					);
				node = _model->getNode(s.id);
				if (!node) {
					qCritical() << "add_plotData failed:" << QString::fromStdString(s.name);
					continue;
				}
			}
			node->plotData->getData()->add(QCPGraphData((s.time-zero)/1000.0, s.value));
		}
	}
}

TreeNode* PlotView::add_plotData( uint64_t id, QSharedPointer<QCPGraphDataContainer> &data, QString plot_name) {

	auto node =_model->add_plotData(id,data,plot_name);
	_treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	_graphView->resetUI(_model);
	return node;
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

void PlotView::enupRang() {
	_graphView->enupRang();
}

void PlotView::setPlotType(int type) {
	if (type != plotType) {
		plotType = type;
		emit plotTypeChanged(plotType);
	}
}


