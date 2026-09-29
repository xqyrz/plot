//
// Created by 25137 on 2026/9/29.
//

#ifndef PLOT_AXFPAGE_H
#define PLOT_AXFPAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class AxfPage;
}
class AxfTree;
QT_END_NAMESPACE

class AxfPage : public QWidget
{
    Q_OBJECT

public:
    explicit AxfPage(QWidget* parent = nullptr);
    ~AxfPage() override;
private slots:
    void on_key_textChanged();
private:
    Ui::AxfPage* ui;
    AxfTree* m_tree;
};


#endif // PLOT_AXFPAGE_H
