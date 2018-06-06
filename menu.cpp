#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 600, 500);
    ui->graphicsView->setScene(scene);
    w1 = scene->addPixmap(QPixmap("/home/wesleylin/ShootingGame/picture/o_side_AWM.png"));
    w1->setPos(20, 60);
    w1->setScale(0.2);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    MainWindow *m = new MainWindow;
    m->show();
    close();
}
