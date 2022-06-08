#ifndef RESULTMENU_H
#define RESULTMENU_H

#include <QDialog>

namespace Ui {
class ResultMenu;
}

class ResultMenu : public QDialog
{
    Q_OBJECT

public:
    explicit ResultMenu(QWidget *parent = nullptr,int time=0,std::string file="");
    ~ResultMenu();

    void displayHallOfFame();
    void editHallOfFame(int time, std::string namePlayer);
    int getItsNumButton() const;
    void setItsNumButton(int value);

private:
    Ui::ResultMenu *ui;
    int itsTime;
    std::string itsFile;
    int itsNumButton;
    //theGameloop *aGameLoop;

private slots:
    void on_menuButton_clicked();
    void on_pushButton_clicked();
    void on_restartButton_clicked();
    void on_nextButton_clicked();
};

#endif // RESULTMENU_H
