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
    QMessageBox msgBox;
    msgBox.addButton("Menu", QMessageBox::AcceptRole)->setFlat(1);
    msgBox.addButton("Close", QMessageBox::RejectRole)->setFlat(1);
    QPalette p;
    p.setBrush(QPalette::Window, QBrush(QColor(55,65,71)));
    p.setBrush(QPalette::Button, QBrush(QColor(55,65,71)));
    p.setBrush(QPalette::WindowText, QBrush(QColor(124,176,176)));
    p.setBrush(QPalette::ButtonText, QBrush(QColor(124,176,176)));
    msgBox.setPalette(p);

    MainWindow *m = new MainWindow(0, this);
    m->show();
    close();
}

void Menu::on_pushButton_2_clicked()
{
    MainWindow *m = new MainWindow(0, 0, this);
    m->show();
    close();
}

void Menu::on_pushButton_3_clicked()
{
    MainWindow *m = new MainWindow(0, 0, 1, this);
    m->show();
    close();
}

void Menu::on_pushButton_4_clicked()
{
    score = new rank(this);
    score->show();
    //close();
}
