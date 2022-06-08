#include "creditmenu.h"
#include "ui_creditmenu.h"

#include "startmenu.h"
#include "ui_startmenu.h"

CreditMenu::CreditMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreditMenu)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":pomme.png"));
    setWindowTitle("I Wanna Be the Guy 2.0 - Crédits");


    setAutoFillBackground(true); // This sentence should be added, otherwise the background image may not be displayed.
    QPixmap backGround(":creditMenu.png");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
    QBrush(backGround));
    setPalette(palette);
    setFixedSize(backGround.size());


    QPixmap pixmap(":menu.png");
    QIcon buttonIcon(pixmap);

    ui->menuButton->setIcon(buttonIcon);
    ui->menuButton->setIconSize(pixmap.rect().size());
    ui->menuButton->setGeometry(250,560,pixmap.width(),pixmap.height());

}

CreditMenu::~CreditMenu()
{
    delete ui;
}

void CreditMenu::on_menuButton_clicked()
{
    StartMenu *MenuStart = new StartMenu;
    MenuStart->show();

    this->close();

}
