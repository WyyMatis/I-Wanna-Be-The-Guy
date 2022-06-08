#include "pausemenu.h"
#include "ui_pausemenu.h"
//#include <QSound>
#include <QDebug>
#include <QIcon>

#include <QStyle>

PauseMenu::PauseMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PauseMenu)
{
    //ui->setupUi(this);

    setWindowIcon(QIcon(":pomme.png"));
    setWindowTitle("I Wanna Be the Guy 2.0 - PAUSE");

    setAutoFillBackground(true); // This sentence should be added, otherwise the background image may not be displayed.
    QPixmap backGround(":backGround.png");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
    QBrush(backGround));
    setPalette(palette);
    setFixedSize(backGround.size());


    QPixmap pixmap(":done.png");
    QIcon buttonIcon(pixmap);
    doneButton = new QPushButton(this);
    doneButton->setIcon(buttonIcon);
    doneButton->setIconSize(pixmap.rect().size());
    doneButton->setFixedSize(pixmap.rect().size());


    pixmap.load(":quit.png");
    QIcon quitIcon(pixmap);
    quitButton = new QPushButton(this);
    quitButton->setIcon(quitIcon);
    quitButton->setIconSize(pixmap.rect().size());
    quitButton->setFixedSize(pixmap.rect().size());

    pixmap.load(":restart.png");
    QIcon restartIcon(pixmap);
    restartButton = new QPushButton(this);
    restartButton->setIcon(restartIcon);
    restartButton->setIconSize(pixmap.rect().size());
    restartButton->setFixedSize(pixmap.rect().size());
    doneButton->setGeometry(217,424,pixmap.width(),pixmap.height());

    quitButton->setGeometry(217,346,pixmap.width(),pixmap.height());
    //pixmap.load(":restart.png");
    restartButton->setGeometry(217,266,pixmap.width(),pixmap.height());
    itsNumButton=0;
    connect(restartButton, SIGNAL(clicked()), this, SLOT(on_restartButton_clicked()));
    connect(doneButton, SIGNAL(clicked()), this, SLOT(on_doneButton_clicked()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(on_quitButton_clicked()));

    //QPushButton#quitButton:hover{background-color: rgba(0,0,0,0.5);}
    //QPushButton#quitButton{background-color:rgba(0,0,0,0); border-radius:15px;}
}

PauseMenu::~PauseMenu()
{
    delete ui;
}

int PauseMenu::getNumButton()
{
    return itsNumButton;
}

void PauseMenu::setNumButton(int x)
{
    itsNumButton=x;
}
void PauseMenu::on_restartButton_clicked()
{
    itsNumButton=3;
    this->close();
}

void PauseMenu::on_quitButton_clicked()
{
    itsNumButton=2;
    MenuDemarrage = new StartMenu;
    MenuDemarrage->show();
    this->close();


}

void PauseMenu::on_doneButton_clicked()
{
    itsNumButton=1;
    this->close();

}

