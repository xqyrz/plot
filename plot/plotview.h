//
// Created by 25137 on 25-9-27.
//

#ifndef PLOTVIEW_H
#define PLOTVIEW_H
#include <QWidget>
#include "plotmodel.h"
#include <QPointer>
#include "qcustomplot/qcustomplot.h"
#include "plotcommon.h"
class QHBoxLayout;
class QCheckBox;
class QComboBox;
class QSpinBox;
class QToolBar;
class PlotTree;
class PlotCustom;
class PlotModel;
class TreeNode;
class  PlotView  : public QWidget
{
    Q_OBJECT
public:
    PlotView(QWidget *parent=nullptr);
    void expandAll()const;
    int getPlotType() const{return plotType;}
     void addSignalData(const QList<IOAPP::SIGNALS>& _signals);
private:

    void initUI();
    void initConnect();
public slots:
    TreeNode* add_plotData( uint64_t id, QSharedPointer<QCPGraphDataContainer>& data, QString plot_name = "plot");
    void setCurrentPlot(int type,const QCPLayerable * item);
    void enupRang();
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
    uint64_t zero;
private:
    Q_PROPERTY(int plotType READ getPlotType WRITE setPlotType)
};



#endif //PLOTVIEW_H
