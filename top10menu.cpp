#include "top10menu.h"
#include "ui_top10menu.h"

#include "startmenu.h"
#include "ui_startmenu.h"

#include <iostream>
#include <fstream>
#include <map>
#include <QListWidgetItem>

using namespace std;

Top10Menu::Top10Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Top10Menu)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":pomme.png"));
    setWindowTitle("I Wanna Be the Guy 2.0 - Top 10");

    setAutoFillBackground(true); // This sentence should be added, otherwise the background image may not be displayed.
    QPixmap backGround(":MenuTop10.png");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
    QBrush(backGround));
    setPalette(palette);
    setFixedSize(backGround.size());


    QPixmap pixmap(":menu.png");;
    ui->menuButton->setIcon(pixmap);
    ui->menuButton->setIconSize(pixmap.size());
    ui->menuButton->setGeometry(272,505,pixmap.width(),pixmap.height());

    ui->listTop10->setGeometry(218,255,225,150);
    ui->radioButtonTuto->setGeometry(200,430,100,20);
    ui->radioButtonTuto->setChecked(true);
    ui->radioButtonLevel1->setGeometry(350,430,100,20);

    ui->radioButtonLevel2->setGeometry(350,460,100,20);

    displayHallOfFame("../protoV4/HallOfFameTuto.txt");
}

Top10Menu::~Top10Menu()
{
    delete ui;
}

void Top10Menu::menu()
{

}

void Top10Menu::on_menuButton_clicked()
{
    StartMenu * MenuStart = new StartMenu;
    MenuStart->show();
    this->close();
}

void Top10Menu::displayHallOfFame(string aFile)
{
    ui->listTop10->clear();

    std::ifstream readHallOfFameFile(aFile);

    std::string name,namePlayer, temps;

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


            QString aQstring = QString::number(i+1) + " " + QString::fromStdString(name) + " " + QString::fromStdString(aTime) + " sec";
            new QListWidgetItem(aQstring, ui->listTop10);
        }
    }
}

void Top10Menu::on_radioButtonTuto_clicked()
{
    displayHallOfFame("../protoV4/HallOfFameTuto.txt");
}

void Top10Menu::on_radioButtonLevel1_clicked()
{
    displayHallOfFame("../protoV4/HallOfFameLevel1.txt");
}

void Top10Menu::on_radioButtonLevel2_clicked()
{
    displayHallOfFame("../protoV4/HallOfFameLevel2.txt");
}
