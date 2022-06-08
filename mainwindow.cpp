#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include <QKeyEvent>
#include <fstream>
#include <ctime>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1000,768);
    setAutoFillBackground(true);
    constructionNiveau();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete aPerson;
    delete itsTimer;
    delete playerTimer;
    itsLevel.clear();
}

void MainWindow::setItsSpeed(double value)
{
    itsSpeed = value;
    Xscreen +=itsSpeed;
    if(Xscreen<0)
    {
        Xscreen=0;

    }
    if(Xscreen>nbrColonne)
    {
        Xscreen=nbrColonne;
    }
    for(double i=0;i<nbrLigne;i++)
    {
        for(double j=0;j<nbrColonne;j++)
        {
            itsLevel[i][j]->calculatePosition(itsSpeed);
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter *painter = new QPainter(this);
    for(double i=Xscreen;i<nbrColonne;i++)
    {
        for(double j=0;j<nbrLigne;j++)
        {
            if(itsLevel[j][i]->getValue()!='0')
            {
                itsLevel[j][i]->draw(painter);
            }
        }
    }
    aPerson->draw(painter);
    painter->end();
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Space && itsTimer->isActive() && !aPerson->getInAir() )
    {
        if(event->isAutoRepeat())
        {
             return;
        }
        aPerson->setJump(true);
        aPerson->resetV_y();
    }

    if(event->key()== Qt::Key_R && !itsTimer->isActive())
    {
        restart();
        start();
    }
    if(event->key()== Qt::Key_Space && !itsTimer->isActive() && !aPerson->intersect(itsLevel,nbrLigne,nbrColonne) && aPerson->calculatePosition()<=48*(nbrLigne+1))
    {
        start();
    }
    if((event->key() == Qt::Key_Left||  event->key() == Qt::Key_Q) && itsTimer->isActive())
    {
        setRunLeft(true);
    }
    if((event->key() == Qt::Key_Right||  event->key() == Qt::Key_D) && itsTimer->isActive() )
    {
        setRunRight(true);
    }
    if(event->key()== Qt::Key_Escape)
    {
        itsTimer->stop();
        exit(0);
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Left ||  event->key() == Qt::Key_Q) && itsTimer->isActive())
    {
        setItsSpeed(0);
        setRunLeft(false);

    }
    if((event->key() == Qt::Key_Right||  event->key() == Qt::Key_D) && itsTimer->isActive())
    {
        setItsSpeed(0);
        setRunRight(false);
    }
    if(event->key() == Qt::Key_Space)
    {
        if(event->isAutoRepeat())
        {
             return;
        }
        aPerson->fall();
    }
}
void MainWindow::gameloop()
{
    aPerson->intersect(itsLevel,nbrLigne,nbrColonne);
    aPerson->calculatePosition();
    if(isRunningLeft)
    {
        if(Xscreen>1)
        {
            setItsSpeed(-0.15);
        }
        else
        {
          setItsSpeed(0);
        }
    }
    if(isRunningRight)
    {
        if(Xscreen<nbrColonne)
        {
           setItsSpeed(0.15);
        }
        else
        {
            setItsSpeed(0);
        } 
    }
    int hauteur;
    for(int i=Xscreen;i<nbrColonne;i++)
    {
        for(int j=0;j<nbrLigne;j++)
        {
            if(itsLevel[j][i]->getValue()!='0')
            {
                if(itsLevel[j][i]->getValue()=='8' || itsLevel[j][i]->getValue()=='6' )
                {
                    if(itsLevel[j][i]->getValue()=='8')
                    {
                        hauteur=720;
                    }
                    else if(itsLevel[j][i]->getValue()=='6')
                    {
                        hauteur=768;
                    }
                    if((aPerson->getRect().x()>(itsLevel[j][i]->getRect().x()-48) && aPerson->getRect().x()<(itsLevel[j][i]->getRect().x()+96)) || itsLevel[j][i]->getFalling())
                    {
                        if((itsLevel[j][i]->getRect().y()+96)>=hauteur)
                        {
                            itsLevel[j][i]->setFalling(false);
                        }
                        else
                        {
                            itsLevel[j][i]->move(4);
                            itsLevel[j][i]->setFalling(true);
                        }
                    }
                }
                if(itsLevel[j][i]->getValue()=='7')
                {
                    itsLevel[j][i]->move(0);
                }
                if(itsLevel[j][i]->getValue()=='9' && (aPerson->getRect().x()>(itsLevel[j][i]->getRect().x()-45) && aPerson->getRect().x()<(itsLevel[j][i]->getRect().x()+45)) && aPerson->getRect().y()>(itsLevel[j][i]->getRect().y()-45) && aPerson->getRect().y()<(itsLevel[j][i]->getRect().y()+45))
                {
                    if(itsLevel[j][i]->getFalling())
                    {
                       bonusTime-=5;
                    }
                    else if(!itsLevel[j][i]->getFalling())
                    {
                        bonusTime+=5;
                    }
                    itsLevel[j][i]->setValue('0');
                }
                if(itsLevel[j][i]->getValue()=='X' ||itsLevel[j][i]->getValue()=='Y')
                {
                    itsLevel[j][i]->move(3);
                    //aPerson->intersect(itsLevel,nbrLigne,nbrColonne);
                }
                if(itsLevel[j][i]->getValue()=='-' && (aPerson->getRect().x()>(itsLevel[j][i]->getRect().x()-50) && aPerson->getRect().x()<(itsLevel[j][i]->getRect().x()+90)) && aPerson->getRect().y()>(itsLevel[j][i]->getRect().y()-50) && aPerson->getRect().y()<(itsLevel[j][i]->getRect().y()+90))
                {
                   itsLevel[j][i]->setValue('2');
                }
                if(itsLevel[j][i]->getValue()=='Z' && (aPerson->getRect().x()>(itsLevel[j][i]->getRect().x()-45) && aPerson->getRect().x()<(itsLevel[j][i]->getRect().x()+90)) && aPerson->getRect().y()>(itsLevel[j][i]->getRect().y()-45) && aPerson->getRect().y()<(itsLevel[j][i]->getRect().y()+90))
                {
                   itsTimer->stop();
                   ui->Result->setText(R"(------------------
      VICTOIRE
--------------------
Appuyer sur R ou Esc)");
                }

            }
        }
    }//aPerson->calculatePosition();
    if(aPerson->calculatePosition()>=48*(nbrLigne+1)||aPerson->intersect(itsLevel,nbrLigne,nbrColonne))
    {
       itsTimer->stop();
       ui->Result->setText(R"(------------------
       PERDU
------------------
Appuyer sur R ou Esc)");
    }
    int timeStart=playerTimer->elapsed();
    int timeEntier;
    //aPerson->calculatePosition();
    timeEntier= (timeStart/1000)+bonusTime;
        timeStart= (timeStart%1000);
        QString theMilli,theSeq;
        theMilli.setNum(timeStart);
        theSeq.setNum(timeEntier);
        if(timeEntier>99)
        {
            ui->temps->setText("Temps:" + theSeq + "." + theMilli);
        }
        else if(timeEntier>9)
        {
            ui->temps->setText("Temps: " + theSeq + "." + theMilli);
        }
        else
        {
            ui->temps->setText("Temps:  " + theSeq + "." + theMilli);
        }

    repaint();
}
void MainWindow::start()
{
    itsTimer->start();
    playerTimer->start();
}
void MainWindow::setRunLeft(bool value)
{
    isRunningLeft=value;
}
void MainWindow::setRunRight(bool value)
{
    isRunningRight=value;
}
void MainWindow::constructionNiveau(){
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
    QBrush(QPixmap(":fondecran.png").scaled(3840,768,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(palette);
    //setStyleSheet("background-image:url(:/media/Qi/kjaulin/PT2/PrepaTerrain/balle.png)");
    ifstream aFile(":niveau1.txt");
    int value;
    string strColonne,strLigne,strValue;
    getline(aFile,strColonne,' ');
    getline(aFile,strLigne);
    string::size_type sz;
    nbrColonne=stoi(strColonne,&sz);
    nbrLigne=stoi(strLigne,&sz);
    vector<tile*> tileLine;
    bool aleaLucky=rand()%2;
    for(int i=0;i<nbrLigne;i++)
    {
        getline(aFile,strValue);

        for(int j=0;j<nbrColonne;j++)
        {
            value=strValue[j];
            if(value=='Y')
            {
                aTile = new block(j*48,i*48,value,"FALL");
            }
            else if(value=='X' )
            {
                aTile = new block(j*48,i*48,value,"SLIDE");
            }
            else if(value =='2')
            {
                aTile = new spike(j*48,i*48,value,1,"NORTH");
            }
            else if(value =='-')
            {
                aTile = new spike(j*48,i*48,value,0,"NORTH");
            }
            else if(value =='3')
            {
                aTile = new spike(j*48,i*48,value,1,"SOUTH");
            }
            else if(value =='4')
            {
                aTile = new spike(j*48,i*48,value,1,"WEST");
            }
            else if(value =='5')
            {
                aTile = new spike(j*48,i*48,value,1,"EAST");
            }
            else if(value =='6')
            {
                aTile = new Apple(j*48,i*48,value,"FALL");
            }
            else if(value =='7')
            {
                aTile = new Apple(j*48,i*48,value,"SLIDE");
            }
            else if(value =='8')
            {
                aTile = new Lightning(j*48,i*48,value,0);
            }
            else if(value =='9')
            {
                aTile = new Piece(j*48,i*48,value,aleaLucky);
                if(aleaLucky)
                {
                 aleaLucky=false;
                }
                else
                {
                 aleaLucky=true;
                }
            }
            else if(value=='0')
            {
                aTile = new tile(j*48,i*48,'0');
            }
            else if(value>='A')
            {
                aTile = new tile(j*48,i*48,value);
            }

            tileLine.push_back(aTile);
        }
        itsLevel.push_back(tileLine);
        tileLine.clear();
    }
    aFile.close();
    aPerson = new Personn();
    itsTimer = new QTimer(this);
    itsTimer->setInterval(10);
    connect(itsTimer,SIGNAL(timeout()),this,SLOT(gameloop()));
    playerTimer = new QElapsedTimer();
}
void MainWindow::restart()
{
    delete aPerson;
    delete itsTimer;
    delete playerTimer;
    for(int i=0;i<nbrLigne;i++)
    {
        for(int j=0;j<nbrColonne;j++)
        {
            delete itsLevel[i][j];
        }
    }
    itsLevel.clear();
    ui->Result->setText("");
    Xscreen=0;
    itsSpeed=0;
    isRunningRight=false;
    isRunningLeft=false;
    bonusTime=0;
    constructionNiveau();
}
