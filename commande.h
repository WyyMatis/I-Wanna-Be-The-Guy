#ifndef COMMANDE_H
#define COMMANDE_H

#include <QMainWindow>
#include <QListWidgetItem>
namespace Ui {
class Commande;
}

class Commande : public QMainWindow
{
    Q_OBJECT

public:
    explicit Commande(QWidget *parent = nullptr);
    ~Commande();

private:
    Ui::Commande *ui;
private slots:
    void on_menuButton_clicked();
};

#endif // COMMANDE_H
