#include "commande.h"
#include "ui_commande.h"

#include "startmenu.h"
#include "ui_startmenu.h"
Commande::Commande(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Commande)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":pomme.png"));
    setWindowTitle("I Wanna Be the Guy 2.0 - Commandes");


    setAutoFillBackground(true); // This sentence should be added, otherwise the background image may not be displayed.
    QPixmap backGround(":Commande.png");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
    QBrush(backGround));
    setPalette(palette);
    setFixedSize(backGround.size());


    QPixmap pixmap(":menu.png");
    QIcon buttonIcon(pixmap);

    ui->menuButton->setIcon(buttonIcon);
    ui->menuButton->setIconSize(pixmap.rect().size());
    ui->menuButton->setGeometry(212,518,pixmap.width(),pixmap.height());
}

Commande::~Commande()
{
    delete ui;
}
void Commande::on_menuButton_clicked()
{
    StartMenu *MenuStart = new StartMenu;
    MenuStart->show();

    this->close();

}
