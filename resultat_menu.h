#ifndef RESULTAT_MENU_H
#define RESULTAT_MENU_H

#include <QDialog>
#include <QMainWindow>
#include <iostream>

#include "thegameloop.h"

QT_BEGIN_NAMESPACE
namespace Ui {class Resultat_Menu;}
QT_END_NAMESPACE

class Resultat_Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Resultat_Menu(QWidget *parent = nullptr);
    ~Resultat_Menu();

    void displayHallOfFame();
    void editHallOfFame(int time, std::string namePlayer);
    void setItsFile(const std::string &value);

    int getItsNumButton() const;
    void setItsNumButton(int value);

    void setItsTime(int value);

private:
    Ui::Resultat_Menu *ui;
    int itsTime;
    std::string itsNameLevel;
    std::string itsFile;
    int itsNumButton;
    //theGameloop *aGameLoop;

private slots:
    void on_menuButton_clicked();
    void on_pushButton_clicked();
    void on_restartButton_clicked();
    void on_nextButton_clicked();
};

#endif // RESULTAT_MENU_H
