//
// Created by 25137 on 2026/9/29.
//

#ifndef PLOT_AXFUI_H
#define PLOT_AXFUI_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class AxfUI;
}
class AxfTree;
QT_END_NAMESPACE

class AxfUI : public QWidget
{
    Q_OBJECT

public:
    explicit AxfUI(QWidget* parent = nullptr);
    ~AxfUI() override;
private slots:
    void on_key_textChanged();
private:
    Ui::AxfUI* ui;
    AxfTree* m_tree;
private:

};


#endif // PLOT_AXFPAGE_H
