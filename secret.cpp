#include "secret.h"
#include "ui_secret.h"

#include "resultat_menu.h"
#include "ui_resultmenu.h"

#include "pausemenu.h"
#include "ui_pausemenu.h"

#include "thegameloop.h"
#include "ui_thegameloop.h"

#include "top10menu.h"
#include "ui_top10menu.h"

#include "creditmenu.h"
#include "ui_creditmenu.h"

#include "commande.h"
#include "ui_commande.h"
#include "thegameloop.h"
#include "ui_thegameloop.h"
Secret::Secret(QWidget *parent,int theTime) :
    QMainWindow(parent),
    ui(new Ui::Secret)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":pomme.png"));
    setWindowTitle("I Wanna Be the Guy 2.0");

    backgroundStart=new QPixmap(":MenuStart.png");
    setFixedSize(backgroundStart->size());


    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(*backgroundStart));
    setPalette(palette);

    QPixmap pixmap(":Jouer.png");
    ui->buttonPlay->setIcon(pixmap);
    ui->buttonPlay->setIconSize(pixmap.size());
    ui->buttonPlay->setGeometry(196,461,pixmap.width(),pixmap.height());

    pixmap.load(":top10.png");
    ui->top10Button->setIcon(pixmap);
    ui->top10Button->setIconSize(pixmap.size());
    ui->top10Button->setGeometry(330,460,pixmap.width(),pixmap.height());

    pixmap.load(":Quitter.png");
    ui->leaveButton->setIcon(pixmap);
    ui->leaveButton->setIconSize(pixmap.size());
    ui->leaveButton->setGeometry(230,525,pixmap.width(),pixmap.height());

    pixmap.load(":credits.png");
    ui->creditButton->setIcon(pixmap);
    ui->creditButton->setIconSize(pixmap.size());
    ui->creditButton->setGeometry(500,740,pixmap.width(),pixmap.height());

    pixmap.load(":commandeButton.png");
    ui->commandeButton->setIcon(pixmap);
    ui->commandeButton->setIconSize(pixmap.size());
    ui->commandeButton->setGeometry(20,740,pixmap.width(),pixmap.height());

    ui->listLevel->setGeometry(163,205,300,152);
    new QListWidgetItem(tr("Niveau Tutoriel"), ui->listLevel);
    new QListWidgetItem(tr("Niveau 1"), ui->listLevel);
    new QListWidgetItem(tr("Niveau 2"), ui->listLevel);
    itsPerson = new Personn();
    playerTimer = new QElapsedTimer();
    itsTimer = new QTimer(this);
    itsTimer->setInterval(10);
    itsTimer->start();
    playerTimer->start();
    itsTime=theTime;
    connect(itsTimer,SIGNAL(timeout()),this,SLOT(gameloop()));
    timerValue=0;
    connect(itsTimer,&QTimer::timeout,[this](){if(timerValue==150)
    {
            timerValue=-1;
    }
    timerValue++;
        });
    Tile *aTile;
    vector<Tile*> tileLine;
    for(int j=0;j<17;j++)
    {
        for(int i=0;i<14;i++)
        {
            if(i==13)
            {
                aTile = new Tile(j*48,i*48,'a');
                tileLine.push_back(aTile);
            }
            else if(i==4 && j>=3 && j<=9)
            {
                aTile = new Tile(j*48,i*48,'a');
                tileLine.push_back(aTile);
            }
            else if(i==2 && j>=4 && j<=9)
            {
                aTile = new Tile(j*48,i*48,'c');
                tileLine.push_back(aTile);
            }
            else if((i==2 && j==3)||(i==8 && j==11))
            {
                aTile = new Tile(j*48,i*48,'b');
                tileLine.push_back(aTile);
            }
            else if((i==2 && j==10)||(i==8 && j==12))
            {
                aTile = new Tile(j*48,i*48,'d');
                tileLine.push_back(aTile);
            }
            else if(i==7 && j==11)
            {
                aTile = new Tile(j*48,i*48,'Z');
                tileLine.push_back(aTile);
            }
            else
            {
                aTile = new Tile(j*48,i*48,'0');
                tileLine.push_back(aTile);
            }

        }
        itsLevel.push_back(tileLine);
        tileLine.clear();
    }
}

Secret::~Secret()
{
    delete ui;
    delete itsPerson;
    delete itsTimer;
    delete backgroundStart;
}
void Secret::mousePressEvent(QMouseEvent * event)
{
    if(event->button()==Qt::LeftButton && event->x()>itsPerson->getRect().x() && event->x()<itsPerson->getRect().x()+48 && event->y()>itsPerson->getRect().y() && event->y()<itsPerson->getRect().y()+48)
    {
        itsPerson->setJump(true);
        itsPerson->resetV_y();
    }
}
void Secret::gameloop()
{
    if(itsPerson->getRect().x()>backgroundStart->size().width()-48 && isRunningRight)
    {

            isRunningRight=false;
            isRunningLeft=true;
           itsPerson->setItsSpeed(-3);
           itsPerson->setItsDirection(true);
    }
    else if(itsPerson->getRect().x()<=0 && isRunningLeft)
    {
            isRunningLeft=false;
            isRunningRight=true;
            itsPerson->setItsSpeed(3);
            itsPerson->setItsDirection(false);
    }
    if(!isRunningLeft && !isRunningRight)
    {
        itsPerson->setItsSpeed(3);
        isRunningRight=true;
    }
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(itsLevel[j][i]->getValue()=='Z' && (itsPerson->getRect().x()>(itsLevel[j][i]->getRect().x()-45) && itsPerson->getRect().x()<(itsLevel[j][i]->getRect().x()+90)) && itsPerson->getRect().y()>(itsLevel[j][i]->getRect().y()-45) && itsPerson->getRect().y()<(itsLevel[j][i]->getRect().y()+90))
            {
                //stageSound->play();
                _sleep(500);
                itsTimer->stop();
                itsTime+=playerTimer->elapsed();
                itsMenuFin = new ResultMenu(nullptr,itsTime,"niveau2.txt");
                if(itsMenuFin->exec()==0)
                {
                    if(itsMenuFin->getItsNumButton()==1 ||itsMenuFin->getItsNumButton()==2 )
                    {
                        this->close();
                    }
                    if(itsMenuFin->getItsNumButton()==3)
                    {
                        TheGameLoop *aGameloop = new TheGameLoop(nullptr,"niveau2.txt");
                        aGameloop->show();
                        itsTimer->stop();

                        this->close();
                    }
                }
            }
        }
    }

    /*if((isRunningLeft &&itsPerson->getRect().x()==336) ||(isRunningRight &&itsPerson->getRect().x()==192))
    {
        itsPerson->setJump(true);
        itsPerson->resetV_y();
    }*/
    itsPerson->intersect(itsLevel,16,14);
    itsPerson->calculatePosition();
    repaint();
}

void Secret::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter *painter = new QPainter(this);
    itsPerson->draw(painter,timerValue);
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<14;j++)
        {
           itsLevel[i][j]->draw(painter,timerValue);
        }

    }
    painter->end();
}

