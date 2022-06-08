#ifndef TOP10MENU_H
#define TOP10MENU_H

#include <QMainWindow>
#include <QListWidgetItem>
namespace Ui {
class Top10Menu;
}

class Top10Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Top10Menu(QWidget *parent = nullptr);
    ~Top10Menu();
    void displayHallOfFame(std::string aFile);

private:
    Ui::Top10Menu *ui;

public slots:
    void menu();
private slots:
    void on_menuButton_clicked();
    void on_radioButtonTuto_clicked();
    void on_radioButtonLevel1_clicked();
    void on_radioButtonLevel2_clicked();
};

#endif // TOP10MENU_H
