//
// Created by 25137 on 2026/10/11.
//

#ifndef PLOT_AXFPAGE_H
#define PLOT_AXFPAGE_H
#include "page/pagebase.h"
#include <QWidget>
class AxfPage:public PageBase
{
    Q_OBJECT
    Q_INTERFACES(PageBase)
    Q_PLUGIN_METADATA(IID PageBase_Id FILE "axfpage.json")
public:
    explicit AxfPage(QWidget* parent=nullptr);
    ~AxfPage() override{};
private:

};


#endif // PLOT_AXFPAGE_H
