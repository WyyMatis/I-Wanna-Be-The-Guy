#ifndef StartMenu_H
#define StartMenu_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <QPixmap>
#include <QMouseEvent>
//#include <QSound>
#include "personn.h"
#include "tile.h"
namespace Ui {
class StartMenu;
}

class StartMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

private slots:
    void on_top10Button_clicked();

    void on_leaveButton_clicked();

    void on_buttonPlay_clicked();
    void gameloop();

    void mousePressEvent(QMouseEvent *event);
    void on_creditButton_clicked();
    void on_commandeButton_clicked();

private:
    Ui::StartMenu *ui;
    QTimer *itsTimer;
    Personn * itsPerson;
    int timerValue;
    vector<vector<Tile*>> itsLevel;
    QPixmap* backgroundStart;
    bool isRunningRight=false;
    bool isRunningLeft=false;
    void paintEvent(QPaintEvent *event);
};

#endif // StartMenu_H
