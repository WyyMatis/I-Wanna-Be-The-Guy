#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QElapsedTimer>
#include "block.h"
#include "spike.h"
#include "personn.h"
#include "apple.h"
#include "lightning.h"
#include "piece.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setItsSpeed(double value);
    void setRunLeft(bool value);
    void setRunRight(bool value);
    void restart();
    void constructionNiveau();
private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
    vector<vector<tile*>> itsLevel;
    QElapsedTimer *playerTimer;
    tile *aTile;
    QTimer *itsTimer;
    Personn *aPerson;
    double Xscreen=0;
    double itsSpeed=0;
    QPixmap theMap;
    double Xcount=0;
    double Ycount=0;
    bool isRunningRight=false;
    bool isRunningLeft=false;
    int bonusTime=0;
    int nbrLigne;
    int nbrColonne;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);



private slots:
    void gameloop();
    void start();

};

#endif // MAINWINDOW_H
