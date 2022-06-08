#ifndef SECRET_H
#define SECRET_H

#include <QMainWindow>

#include <QTimer>
#include <vector>
#include <QPixmap>
#include <QMouseEvent>
//#include <QSound>
#include <QElapsedTimer>
#include "personn.h"
#include "tile.h"
#include "resultmenu.h"
#include "ui_resultmenu.h"
namespace Ui {
class Secret;
}

class Secret : public QMainWindow
{
    Q_OBJECT

public:
    explicit Secret(QWidget *parent = nullptr,int theTime=0);
    ~Secret();
private slots:
    void gameloop();

    void mousePressEvent(QMouseEvent *event);
private:
    Ui::Secret *ui;
    QTimer *itsTimer;
    QElapsedTimer * playerTimer;
    int itsTime;
    Personn * itsPerson;
    int timerValue;
    vector<vector<Tile*>> itsLevel;
    ResultMenu * itsMenuFin;
    QPixmap* backgroundStart;

    bool isRunningRight=false;
    bool isRunningLeft=false;
    void paintEvent(QPaintEvent *event);
};

#endif // SECRET_H
