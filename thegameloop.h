#ifndef TheGameLoop_H
#define TheGameLoop_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QElapsedTimer>
#include <QKeyEvent>
//#include <QSound>
#include "resultmenu.h"
#include "ui_resultmenu.h"

#include "pausemenu.h"
#include "ui_pausemenu.h"
#include "secret.h"
#include "ui_secret.h"


#include "block.h"
#include "spike.h"
#include "personn.h"
#include "apple.h"
#include "lightning.h"
#include "piece.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TheGameLoop; }
QT_END_NAMESPACE

class TheGameLoop : public QMainWindow
{
    Q_OBJECT

public:
    TheGameLoop(QWidget *parent = nullptr,std::string aFileName="");
    ~TheGameLoop();
    void setItsSpeed(double speed);
    void setRunLeft(bool runLeft);
    void setRunRight(bool runRight);
    void restart();
    void constructionNiveau();
private:
    Ui::TheGameLoop *ui;
    void paintEvent(QPaintEvent *event);
    vector<vector<Tile*>> itsLevel;
    QElapsedTimer *playerTimer;
    QTimer *itsTimer;
    Personn *aPerson;
    double Xscreen=0;
    double itsSpeed=0;
    QPixmap theMap;
    bool isRunningRight=false;
    bool isRunningLeft=false;
    int bonusTime=0;
    int nbrLigne;
    int nbrColonne;
    int timerValue;
    int verifyState;
    std::string itsFile;
    PauseMenu * MenuPause ;
    ResultMenu * itsMenuFin;
    Secret * menuSecret;
    /*QSound *pauseSound;
    QSound *coinSound;
    QSound *stageSound;
    QSound *gameoverSound;
    QSound *dieSound;*/

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void getNumButton(int x);

private slots:
    void gameloop();
    void commencerTimer();

};
#endif // TheGameLoop_H
