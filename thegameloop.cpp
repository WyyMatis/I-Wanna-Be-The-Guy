#include "thegameloop.h"
#include "ui_thegameloop.h"

#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include <fstream>
#include <ctime>
#include <QDebug>
//#include <QSound>
TheGameLoop::TheGameLoop(QWidget *parent,std::string aFileName) :
    QMainWindow(parent),
    ui(new Ui::TheGameLoop)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":pomme.png"));
    setWindowTitle("I Wanna Be the Guy 2.0 - "+ QString::fromStdString(aFileName));

    itsFile=aFileName;
    if(itsFile!="secret.txt")
    {
      setFixedSize(1000,768);
    }
    else if(itsFile =="secret.txt")
    {
        setFixedSize(624,768);
    }

    setAutoFillBackground(true);


    if(itsFile != "levelTuto.txt")
    {
        ui->labelTuto1->setVisible(false);
        ui->labelTuto2->setVisible(false);
        ui->labelTuto3->setVisible(false);
        ui->labelTuto4->setVisible(false);
    }
    this->constructionNiveau();
    /*pauseSound= new QSound(":pause.wav");
    coinSound= new QSound(":coinsound.wav");
    stageSound= new QSound(":stageClear.wav");
    gameoverSound= new QSound(":gameOver.wav");
    dieSound= new QSound(":marioDie.wav");*/

}

TheGameLoop::~TheGameLoop()
{
    delete ui;
    delete aPerson;
    delete itsTimer;
    delete playerTimer;
    /*delete pauseSound;
    delete coinSound;
    delete stageSound;
    delete gameoverSound;
    delete dieSound;*/
    itsLevel.clear();
}

void TheGameLoop::setItsSpeed(double value)
{
    itsSpeed = value;
    Xscreen +=itsSpeed;
    if(Xscreen<0)
    {
        Xscreen=0;

    }
    if(Xscreen>nbrColonne-21)
    {
        Xscreen=nbrColonne-21;
    }
    for(double i=0;i<nbrLigne;i++)
    {
        for(double j=0;j<nbrColonne;j++)
        {
            itsLevel[i][j]->calculatePosition(itsSpeed);
        }
    }
}

void TheGameLoop::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter *painter = new QPainter(this);
    for(double i=Xscreen;i<nbrColonne;i++)
    {
        for(double j=0;j<nbrLigne;j++)
        {
            if(itsLevel[j][i]->getValue()!='0')
            {
                itsLevel[j][i]->draw(painter,timerValue);
            }
        }
    }
    aPerson->draw(painter,timerValue);
    painter->end();
}
void TheGameLoop::keyPressEvent(QKeyEvent * event)
{

    if(event->key() == Qt::Key_Space && itsTimer->isActive()&& verifyState!=0)
    {
        if(event->isAutoRepeat())
        {
             return;
        }
        if(verifyState==2)
        {
            aPerson->setJump(true);
            aPerson->resetV_y();
        }
        else if(verifyState==3)
        {
            aPerson->setJump(true);
            aPerson->resetV_y();
        }
        if(!aPerson->getInAir())
        {
            aPerson->setJump(true);
            aPerson->resetV_y();
        }
    }
   else if(event->key()==Qt::Key_Space && itsTimer->isActive() && (!aPerson->getInAir() || !aPerson->getDoubleJump()))
    {

        if(event->isAutoRepeat())
        {
             return;
        }
        if(aPerson->getInAir())
        {
            aPerson->setDoubleJump(true);
        }
        aPerson->setJump(true);
        aPerson->resetV_y();
    }
    if(event->key()== Qt::Key_R)
    {
        if(!itsTimer->isActive())
        {
            //gameoverSound->stop();
            //dieSound->stop();
            restart();
            commencerTimer();
        }

    }
    if(event->key()== Qt::Key_Space && !itsTimer->isActive() && !aPerson->intersect(itsLevel,nbrLigne,nbrColonne) && aPerson->calculatePosition()<=48*(nbrLigne+1))
    {
        commencerTimer();
        ui->labelTuto1->setVisible(false);
        ui->labelTuto2->setVisible(false);
        ui->labelTuto3->setVisible(false);
        ui->labelTuto4->setVisible(false);

    }
    if((event->key() == Qt::Key_Left||  event->key() == Qt::Key_Q) && itsTimer->isActive())
    {
        if(verifyState!=3)
        {
            setRunLeft(true);
            aPerson->setItsDirection(true);
        }

    }
    if((event->key() == Qt::Key_Right||  event->key() == Qt::Key_D) && itsTimer->isActive() )
    {
        if(verifyState!=2)
        {
            setRunRight(true);
            aPerson->setItsDirection(false);
        }

    }
    if(event->key()== Qt::Key_Escape)
    {
        if(itsTimer->isActive())
        {
            MenuPause = new PauseMenu;

            //pauseSound->play();
            MenuPause->setNumButton(0);
            itsTimer->stop();
            if(MenuPause->exec()==0)
            {
                if(MenuPause->getNumButton()==1)
                {
                    itsTimer->start();
                    playerTimer->restart();
                }
                if(MenuPause->getNumButton()==2)
                {
                    this->close();
                }
                if(MenuPause->getNumButton()==3)
                {
                    this->restart();
                    this->commencerTimer();
                }
                //pauseSound->play();
            }

        }

    }

}

void TheGameLoop::keyReleaseEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Left ||  event->key() == Qt::Key_Q) && itsTimer->isActive())
    {
        aPerson->setItsSpeed(0);
        setItsSpeed(0);
        setRunLeft(false);

    }
    if((event->key() == Qt::Key_Right||  event->key() == Qt::Key_D) && itsTimer->isActive())
    {
        aPerson->setItsSpeed(0);
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
void TheGameLoop::gameloop()
{
    verifyState=aPerson->intersect(itsLevel,nbrLigne,nbrColonne);
    aPerson->calculatePosition();
    if(verifyState!=3)
    {
        if(isRunningLeft)
        {
            if(Xscreen>0)
            {
                setItsSpeed(-0.15);
            }
            else
            {
              setItsSpeed(0);
            }
        }
    }
    if(verifyState!=2)
    {
        if(isRunningRight)
        {
            if(Xscreen<nbrColonne-21)
            {
               setItsSpeed(0.15);
               aPerson->setItsSpeed(0);
            }
            else
            {
                setItsSpeed(0);
                aPerson->setItsSpeed(3);
            }
        }
    }
    int hauteur;
    Tile * aTile;
    for(int i=Xscreen;i<nbrColonne;i++)
    {
        for(int j=0;j<nbrLigne;j++)
        {
            if(itsLevel[j][i]->getValue()!='0')
            {
                if(((itsLevel[j][i]->getValue()=='M' && aPerson->getRect().y()>=itsLevel[j][i]->getRect().y())|| ( itsLevel[j][i]->getValue()=='R' && aPerson->getRect().y()<itsLevel[j][i]->getRect().y() ))&& aPerson->getRect().x()+aPerson->getRect().width()>itsLevel[j][i]->getRect().x() && aPerson->getRect().x()<itsLevel[j][i]->getRect().x()+itsLevel[j][i]->getRect().width())
                {
                      if(itsLevel[j][i]->getValue()=='M')
                      {
                          aTile=new Apple(itsLevel[j][i]->getRect().x(),itsLevel[j][i]->getRect().y(),'6',"FALL");
                      }
                      if(itsLevel[j][i]->getValue()=='R')
                      {
                          aTile=new Apple(itsLevel[j][i]->getRect().x(),itsLevel[j][i]->getRect().y(),'6',"UP");
                      }
                      itsLevel[j-1][i]=aTile;
                      itsLevel[j][i]=new Tile(itsLevel[j][i]->getRect().x(),itsLevel[j][i]->getRect().y(),'m');
                }
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
                    //coinSound->play();
                    itsLevel[j][i]->setValue('0');
                }
                if(itsLevel[j][i]->getValue()=='X' ||itsLevel[j][i]->getValue()=='Y' || itsLevel[j][i]->getValue()=='W')
                {
                    itsLevel[j][i]->move(1);
                }
                if(itsLevel[j][i]->getValue()=='-' && (aPerson->getRect().x()>(itsLevel[j][i]->getRect().x()-50) && aPerson->getRect().x()<(itsLevel[j][i]->getRect().x()+90)) && aPerson->getRect().y()>(itsLevel[j][i]->getRect().y()-50) && aPerson->getRect().y()<(itsLevel[j][i]->getRect().y()+90))
                {
                   itsLevel[j][i]->setValue('2');
                }
                if(itsLevel[j][i]->getValue()=='Z' && (aPerson->getRect().x()>(itsLevel[j][i]->getRect().x()-45) && aPerson->getRect().x()<(itsLevel[j][i]->getRect().x()+90)) && aPerson->getRect().y()>(itsLevel[j][i]->getRect().y()-45) && aPerson->getRect().y()<(itsLevel[j][i]->getRect().y()+90))
                {
                    //stageSound->play();
                    ui->Result->setText(R"(------------------
      VICTOIRE
--------------------
Appuyer sur R ou Esc)");
                    //_sleep(500);
                    itsTimer->stop();
                    itsMenuFin = new ResultMenu(nullptr,playerTimer->elapsed(),itsFile);
                    itsMenuFin->setItsNumButton(0);

                    if(itsMenuFin->exec()==0)
                    {
                        if(itsMenuFin->getItsNumButton()==1 ||itsMenuFin->getItsNumButton()==2 )
                        {
                            this->close();
                        }
                        if(itsMenuFin->getItsNumButton()==3)
                        {
                            itsTimer->stop();
                            //stageSound->stop();
                            this->restart();
                            this->commencerTimer();
                        }
                    }

                }
                if(itsLevel[j][i]->getValue()=='?' && (aPerson->getRect().x()>(itsLevel[j][i]->getRect().x()-45) && aPerson->getRect().x()<(itsLevel[j][i]->getRect().x()+90)) && aPerson->getRect().y()>(itsLevel[j][i]->getRect().y()-45) && aPerson->getRect().y()<(itsLevel[j][i]->getRect().y()+90))
                {
                    //stageSound->play();
                    ui->Result->setText(R"(------------------
      VICTOIRE
--------------------
Appuyer sur R ou Esc)");
                    //_sleep(500);
                    itsTimer->stop();
                    menuSecret= new Secret(nullptr,playerTimer->elapsed());
                    menuSecret->show();
                    this->close();//itsMenuFin->setItsNumButton(0);

                    /*if(secretEnd->exec()==0)
                    {
                        if(itsMenuFin->getItsNumButton()==1 ||itsMenuFin->getItsNumButton()==2 )
                        {
                            this->close();
                        }
                        if(itsMenuFin->getItsNumButton()==3)
                        {
                            itsTimer->stop();
                            stageSound->stop();
                            this->restart();
                            this->commencerTimer();
                        }
                    }*/

                }

            }
        }
    }
    int timeStart=playerTimer->elapsed();
    int timeEntier;
    //aPerson->calculatePosition();
    timeEntier= (timeStart/1000)+bonusTime;
    timeStart= (timeStart%1000);
    QString theMilli,theSeq;
    theMilli.setNum(timeStart);
    theSeq.setNum(timeEntier);
    if(timeEntier>9)
    {
        ui->temps->setText("Temps: " + theSeq + "." + theMilli);
    }
    else
    {
        ui->temps->setText("Temps:  " + theSeq + "." + theMilli);
    }
    if(aPerson->calculatePosition()>=48*(nbrLigne+1)||verifyState==1 || timeEntier>99) // enlever le 1er pr enlever detect vide
    {
        if(timeEntier>99)
        {
            //gameoverSound->play();
        }
        else
        {
            //dieSound->play();
        }
       itsTimer->stop();
       ui->Result->setText(R"(------------------
       PERDU
------------------
Appuyer sur R ou Esc)");
    }

    repaint();
}
void TheGameLoop::commencerTimer()
{
    itsTimer->start();
    playerTimer->start();
}
void TheGameLoop::setRunLeft(bool value)
{
    isRunningLeft=value;
}
void TheGameLoop::setRunRight(bool value)
{
    isRunningRight=value;
}
void TheGameLoop::constructionNiveau(){
    QPalette palette;
    if(itsFile!="secret.txt")
    {
        palette = this->palette();
        palette.setBrush(QPalette::Window,
        QBrush(QPixmap(":fondecran.png").scaled(3840,768,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        setPalette(palette);
    }
    else if(itsFile=="secret.txt")
    {
        palette = this->palette();
        palette.setBrush(QPalette::Window,
        QBrush(QPixmap(":fondecran.png").scaled(672,768,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        setPalette(palette);
    }

    //setStyleSheet("background-image:url(:/media/Qi/kjaulin/PT2/PrepaTerrain/balle.png)");
    ifstream aFile("../protoV4/"+itsFile);


    int value;
    string strColonne,strLigne,strValue;
    getline(aFile,strColonne,' ');
    getline(aFile,strLigne);
    string::size_type sz;
    nbrColonne=stoi(strColonne,&sz);
    nbrLigne=stoi(strLigne,&sz);
    vector<Tile*> tileLine;
    bool aleaLucky=rand()%2;
    Tile *aTile;
    for(int i=0;i<nbrLigne;i++)
    {
        getline(aFile,strValue);

        for(int j=0;j<nbrColonne;j++)
        {
            value=strValue[j];
            if(value>='1'&& value<='9' && (strValue[j-1]=='X' || strValue[j-1]=='Y'))
            {
                if(strValue[j-1]=='X')
                {
                  tileLine[j-1]->setX(value);
                }

                else if(strValue[j-1]=='Y')
                {
                    tileLine[j-1]->setY(value);
                }
                aTile = new Tile(j*48,i*48,'0');
            }
            else if(value=='Y')
            {
                aTile = new Block(j*48,i*48,value,"FALL");
            }
            else if(value=='X' )
            {
                aTile = new Block(j*48,i*48,value,"SLIDE");
            }
            else if(value=='W' )
            {
                aTile = new Block(j*48,i*48,value,"POP");
            }
            else if(value =='2')
            {
                aTile = new Spike(j*48,i*48,value);
            }
            else if(value =='-')
            {
                aTile = new Spike(j*48,i*48,value);
            }
            else if(value =='3')
            {
                aTile = new Spike(j*48,i*48,value);
            }
            else if(value =='4')
            {
                aTile = new Spike(j*48,i*48,value);
            }
            else if(value =='5')
            {
                aTile = new Spike(j*48,i*48,value);
            }
            else if(value =='6')
            {
                aTile = new Apple(j*48,i*48+48,value,"FALL");
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
                aTile = new Tile(j*48,i*48,'0');
            }
            else if(value>='A' || value=='?')
            {
                aTile = new Tile(j*48,i*48,value);
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
    playerTimer = new QElapsedTimer();
    connect(itsTimer,SIGNAL(timeout()),this,SLOT(gameloop()));
    timerValue=0;
    connect(itsTimer,&QTimer::timeout,[this](){if(timerValue==150)
    {
            timerValue=-1;
    }
    timerValue++;
        });
}
void TheGameLoop::restart()
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
    verifyState=0;
    timerValue=0;
    nbrLigne=0;
    nbrColonne=0;
    this->constructionNiveau();
}
