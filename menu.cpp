#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    MainWindow *m = new MainWindow(0);
    m->show();
    close();
}

void Menu::on_pushButton_2_clicked()
{
    MainWindow *m = new MainWindow(0, 0);
    m->show();
    close();
}

void Menu::on_pushButton_3_clicked()
{

}
