//
// Created by 25137 on 25-9-27.
//

#ifndef PLOTVIEW_H
#define PLOTVIEW_H
#include <QPointer>
#include <QWidget>
#include "../../../common/plug/interfacebase.h"
#include "../../../common/plug/page/pagebase.h"
#include "plotcommon.h"
#include "plotmodel.h"
#include "qcustomplot/qcustomplot.h"
class QHBoxLayout;
class QCheckBox;
class QComboBox;
class QSpinBox;
class QToolBar;
class PlotTree;
class PlotCustom;
class PlotModel;
class TreeNode;
class  PlotView  : public QWidget,public PageBase
{
    Q_OBJECT
    Q_INTERFACES(PageBase)
    Q_PLUGIN_METADATA(IID PageBase_Id FILE "plot.json")
public:
    explicit PlotView(QWidget *parent=nullptr);
    ~PlotView() override;
    void expandAll()const;
    int getPlotType() const{return plotType;}
     void addSignalData(const INC::_SIGNALS& _signal);

     const char* getSignal(int index) const;
     const char* getSlot(int index) const;
private:

    void initUI();
    void initConnect();
public slots:
    TreeNode* add_plotData( uint64_t id, QSharedPointer<QCPGraphDataContainer>& data, const QString plot_name = "plot",int group = 0);
    void setCurrentPlot(int type,const QCPLayerable * item);
    void enupRang();
    void _addSignalData(const QList<INC::_SIGNALS>& _signals);
private slots:
    void setPlotType(int type);

signals:
    void plotTypeChanged(int type);
private:
    QPointer<PlotCustom> _graphView;
    QPointer<PlotTree> _treeView;
    QPointer<QToolBar> _toolBar;
    QPointer<QComboBox> _modleComboBox;
    QPointer<QCheckBox> _xCheckBox;
    QPointer<QSpinBox> _xSpinBox;

    QPointer<PlotModel> _model;
    int plotType;
    double zero=0;
    static  PlotView* m_plotView;
private:
    Q_PROPERTY(int plotType READ getPlotType WRITE setPlotType)
};



#endif //PLOTVIEW_H
