#include "resultat_menu.h"
#include "ui_resultat_menu.h"

#include "startmenu.h"
#include "ui_startmenu.h"

#include <iostream>
#include <fstream>
#include <map>
#include <QWidgetList>

using namespace std;

Resultat_Menu::Resultat_Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resultat_Menu)
{
    //ui->setupUi(this);

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

    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(on_menuButton_clicked()));
    connect(ui->restartButton,SIGNAL(clicked()),this,SLOT(on_menuButton_clicked()));
    connect(ui->menuButton,SIGNAL(clicked()),this,SLOT(on_menuButton_clicked()));
    displayHallOfFame();
}


Resultat_Menu::~Resultat_Menu()
{
    delete ui;
}

void Resultat_Menu::setItsFile(const std::string &value)
{
    if(value == "niveau1.txt")
    {
        itsFile = "../protoV4/HallOfFameLevel1.txt";
    }
    else if (value == "levelTuto.txt")
    {
        itsFile = "../protoV4/HallOfFameTuto.txt";
    }
}

int Resultat_Menu::getItsNumButton() const
{
    return itsNumButton;
}

void Resultat_Menu::setItsNumButton(int value)
{
    itsNumButton = value;
}

void Resultat_Menu::setItsTime(int value)
{
    itsTime = value;
}

void Resultat_Menu::on_menuButton_clicked()
{
    itsNumButton = 1;
    startmenu * MenuStart = new startmenu;
    MenuStart->show();
    this->close();
}

void Resultat_Menu::displayHallOfFame()
{
    ifstream readHallOfFameFile(itsFile);

    string name,namePlayer, temps;

    if(readHallOfFameFile)
    {

        for(int i=0; i<10; ++i)
        {
            getline(readHallOfFameFile, name, ' ');
            getline(readHallOfFameFile, temps);

            //intTemps = stoi(temps);
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


            QString aQstring = QString::number(i+1) + " " + QString::fromStdString(name) + " " + QString::fromStdString(aTime) + " sec";
            new QListWidgetItem(aQstring, ui->listWidgetHallOfFame);
        }
    }
}

void Resultat_Menu::editHallOfFame(int time, string namePlayer)
{
    ifstream readHallOfFameFile(itsFile);
    ui->listWidgetHallOfFame->clear();
    string name, temps;
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




void Resultat_Menu::on_pushButton_clicked()
{
    //QString name = ui->lineEdit->text();
    editHallOfFame(itsTime, ui->lineEdit->text().toStdString());
}

void Resultat_Menu::on_restartButton_clicked()
{
    itsNumButton = 3;
    this->close();
}

void Resultat_Menu::on_nextButton_clicked()
{
    theGameloop *aGameLoop = new theGameloop;
    itsNumButton = 2;
    aGameLoop = new theGameloop(nullptr,"niveau1.txt");
    aGameLoop->show();
    this->close();
}
