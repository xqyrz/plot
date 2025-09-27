//
// Created by 25137 on 25-9-27.
//

#ifndef PLOTVIEW_H
#define PLOTVIEW_H

#include <QWidget>
#include <QPointer>
#include "qcustomplot/qcustomplot.h"
#include "plotcommon.h"
class QHBoxLayout;
class QCheckBox;
class QComboBox;
class QToolBar;
class PlotTree;
class PlotCustom;
class PlotModel;

class  PlotView  : public QWidget
{
    Q_OBJECT
public:
    PlotView(QWidget *parent=nullptr);
    void expandAll()const;
    int getPlotType() const{return plotType;}
private:
    void initUI();
    void initConnect();
public slots:
    void add_plotData(const QSharedPointer<QCPGraphDataContainer>& data, QString plot_name = "plot");
private slots:
    void setPlotType(int type);
signals:
    void plotTypeChanged(int type);
private:
    QPointer<PlotCustom> _graphView;
    QPointer<PlotTree> _treeView;
    QPointer<QToolBar> _toolBar;
    QPointer<QComboBox> _modleComboBox;

    QPointer<PlotModel> _model;
    int plotType;
private:
    Q_PROPERTY(int plotType READ getPlotType WRITE setPlotType)
};



#endif //PLOTVIEW_H
