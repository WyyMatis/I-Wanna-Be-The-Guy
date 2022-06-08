#ifndef CREDITMENU_H
#define CREDITMENU_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {class CreditMenu;}
QT_END_NAMESPACE

class CreditMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreditMenu(QWidget *parent = nullptr);
    ~CreditMenu();

private slots:
    void on_menuButton_clicked();

private:
    Ui::CreditMenu *ui;
};

#endif //CREDITMENU_H
