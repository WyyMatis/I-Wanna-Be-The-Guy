#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QDialog>
#include <QMouseEvent>
#include <QKeyEvent>
//#include <QSound>
#include "startmenu.h"
QT_BEGIN_NAMESPACE
namespace Ui { class PauseMenu; }
QT_END_NAMESPACE

class PauseMenu : public QDialog
{
    Q_OBJECT

public:
    PauseMenu(QWidget *parent = nullptr);
    ~PauseMenu();
    int getNumButton();
    void setNumButton(int x);
    QPushButton * quitButton;
    QPushButton *doneButton;
    QPushButton *restartButton;
    StartMenu *MenuDemarrage;


public slots:
    void on_quitButton_clicked();
    void on_doneButton_clicked();
    void on_restartButton_clicked();
private:
    Ui::PauseMenu *ui;
    int itsNumButton;
};
#endif // PAUSEMENU_H
