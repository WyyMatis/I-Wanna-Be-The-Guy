#include "resultmenu.h"
#include "ui_resultmenu.h"

#include "startmenu.h"
#include "ui_startmenu.h"

#include "thegameloop.h"
#include "ui_thegameloop.h"

#include <iostream>
#include <fstream>
#include <map>
#include <QWidgetList>

using namespace std;

ResultMenu::ResultMenu(QWidget *parent,int time,string file) :
    QDialog(parent),
    ui(new Ui::ResultMenu)
{
    ui->setupUi(this);
    itsTime = time;
    setAutoFillBackground(true); // This sentence should be added, otherwise the background image may not be displayed.
    QPixmap backGround(":Resultat.png");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
    QBrush(backGround));
    setPalette(palette);
    setFixedSize(backGround.size());


    QPixmap pixmap(":suivant.png");
    ui->nextButton->setIcon(pixmap);
    ui->nextButton->setIconSize(pixmap.size());
    ui->nextButton->setGeometry(337,472,pixmap.width(),pixmap.height());
    pixmap.load(":menu.png");
    ui->menuButton->setIcon(pixmap);
    ui->menuButton->setIconSize(pixmap.size());
    ui->menuButton->setGeometry(217,525,pixmap.width(),pixmap.height());
    pixmap.load(":rejouer.png");
    ui->restartButton->setIcon(pixmap);
    ui->restartButton->setIconSize(pixmap.size());
    ui->restartButton->setGeometry(217,470,pixmap.width(),pixmap.height());

    ui->lineEdit->setGeometry(230,417,200,25);
    ui->pushButton->setGeometry(400,445,50,20);
    ui->listWidgetHallOfFame->setGeometry(218,255,225,150);
    itsFile=file;
    ui->lineEdit->setPlaceholderText("Entrer pseudo ici");
    if(itsFile== "niveau1.txt")
    {
        itsFile = "../protoV4/HallOfFameLevel1.txt";
    }
    else if(itsFile== "niveau2.txt")
    {
        itsFile = "../protoV4/HallOfFameLevel2.txt";
        ui->nextButton->setVisible(false);
    }
    else
    {
        itsFile = "../protoV4/HallOfFameTuto.txt";
    }
    displayHallOfFame();
}


ResultMenu::~ResultMenu()
{
    delete ui;
}

int ResultMenu::getItsNumButton() const
{
    return itsNumButton;
}

void ResultMenu::setItsNumButton(int value)
{
    itsNumButton = value;
}

void ResultMenu::on_menuButton_clicked()
{
    itsNumButton = 1;
    StartMenu * MenuStart = new StartMenu;
    MenuStart->show();
    this->close();
}

void ResultMenu::displayHallOfFame()
{
    ifstream readHallOfFameFile(itsFile);

    string name,namePlayer, temps;

    if(readHallOfFameFile)
    {

        for(int i=0; i<10; ++i)
        {
            getline(readHallOfFameFile, name, ' ');
            getline(readHallOfFameFile, temps);
            string aTime = "       ";
            for(int j=0; j < temps.size()+1; ++j)
            {
                if(temps.size() == 4)
                {
                    if(j == 1)
                    {
                        aTime[2] = '.';
                    }
                    else if(j<1)
                    {
                        aTime[j] = temps[j];
                    }
                    else
                    {
                        aTime[j+1] = temps[j-1];
                    }
                }
                if(temps.size() == 5)
                {
                    if(j == 2)
                    {
                        aTime[3] = '.';

                    }
                    else if (j<2)
                    {
                        aTime[j] = temps[j];
                    }
                    else
                    {
                        aTime[j+1] = temps[j-1];
                    }
                }
            }

            if(i==9)
            {
                int temp= stoi(temps);
                double theTime=(double)temp/1000;
                double timerJoueur= (double)itsTime/1000;
                if(timerJoueur>theTime)
                {
                    ui->lineEdit->setVisible(false);
                    ui->pushButton->setVisible(false);
                }
            }
            QString aQstring = QString::number(i+1) + " " + QString::fromStdString(name) + " " + QString::fromStdString(aTime) + " sec";
            new QListWidgetItem(aQstring, ui->listWidgetHallOfFame);
        }
    }
}

void ResultMenu::editHallOfFame(int time, string namePlayer)
{
    ifstream readHallOfFameFile(itsFile);
    ui->listWidgetHallOfFame->clear();
    string name, temps="1";
    int intTemps;

    map<int,string>classement;

    if(readHallOfFameFile)
    {
        classement.insert(std::pair<int,string>(time,namePlayer));

        for(int i=0; i<11; ++i)
        {
            getline(readHallOfFameFile, name, ' ');
            getline(readHallOfFameFile, temps);

            intTemps = stoi(temps);

            classement.insert(std::pair<int,string>(intTemps,name));
        }
    }

    ofstream writeHallOfFame1(itsFile);
    int i=0;
    for(map<int,string>::iterator it=classement.begin(); it!=classement.end(); ++it)
    {
        ofstream writeHallOfFame(itsFile, ios::app);
        writeHallOfFame<<it->second<<" "<<it->first<<endl;

        if (i ==9)
        {
            break;
        }
        i++;
    }
    displayHallOfFame();
}

void ResultMenu::on_pushButton_clicked()
{
    //QString name = ui->lineEdit->text();
    if((ui->lineEdit->text().toStdString()!=""&& ui->lineEdit->text().toStdString()!="16 char. max")  && ui->lineEdit->text().toStdString().length()<=16)
    {
        editHallOfFame(itsTime, ui->lineEdit->text().toStdString());
    }
    if(ui->lineEdit->text().toStdString().length()>16)
    {
        ui->lineEdit->setText("");
        ui->lineEdit->setPlaceholderText("16 characters max");
    }

}

void ResultMenu::on_restartButton_clicked()
{
    itsNumButton = 3;
    this->close();
}

void ResultMenu::on_nextButton_clicked()
{
    TheGameLoop *aGameLoop;
    itsNumButton = 2;
    string nomNiveau="";
    if(itsFile=="../protoV4/HallOfFameTuto.txt")
    {
        nomNiveau="niveau1.txt";
    }
    if(itsFile=="../protoV4/HallOfFameLevel1.txt")
    {
        nomNiveau="niveau2.txt";
    }
    aGameLoop = new TheGameLoop(nullptr,nomNiveau);
    aGameLoop->show();
    this->close();
}
