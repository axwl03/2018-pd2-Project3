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
    SelectWindow *s = new SelectWindow("Select Player1", this);
    int result = s->exec();
    delete s;
    if(result == 0){
        show();
        return;
    }
    m = new MainWindow(result - 1, this);//result-1 is the character ID
    m->show();
    close();
}
void Menu::on_pushButton_2_clicked()
{
    SelectWindow *s1 = new SelectWindow("Select Player1", this);
    SelectWindow *s2 = new SelectWindow("Select Player2");
    int result1 = 0, result2 = 0;
    while(result1 == 0 || result2 == 0){
        result1 = s1->exec();
        if(result1 == 0){
            show();
            return;
        }result2 = s2->exec();
        if(result2 == 0)
            continue;
        if(result1 != 0 && result2 != 0)
            break;
    }
    m = new MainWindow(result1 - 1, result2 - 1, this);
    m->show();
    close();
}

void Menu::on_pushButton_3_clicked()
{
    SelectWindow *s1 = new SelectWindow("Select Player1", this);
    SelectWindow *s2 = new SelectWindow("Select Player2");
    int result1 = 0, result2 = 0;
    while(result1 == 0 || result2 == 0){
        result1 = s1->exec();
        if(result1 == 0){
            show();
            return;
        }result2 = s2->exec();
        if(result2 == 0)
            continue;
        if(result1 != 0 && result2 != 0)
            break;
    }
    m = new MainWindow(result1 - 1, result2 - 1, 1, this);
    m->show();
    close();
}

void Menu::on_pushButton_4_clicked()
{
    score = new rank(this);
    score->show();
    //close();
}
