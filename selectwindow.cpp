#include "selectwindow.h"
#include "ui_selectwindow.h"

SelectWindow::SelectWindow(QString str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectWindow)
{
    if(parent != NULL)
        parent->close();
    p1.setColor(QPalette::Button, QColor(200,200,200));
    p2.setColor(QPalette::Button, QColor(40,150,40));
    ui->setupUi(this);
    ui->label->setText(str);
    ui->pushButton->setIcon(QPixmap("./picture/killer_AWM.png"));
    ui->pushButton->setIconSize(QSize(200,200));
    ui->pushButton->setPalette(p1);
    ui->pushButton_2->setIcon(QPixmap("./picture/officer_shotgun.png"));
    ui->pushButton_2->setIconSize(QSize(200,200));
    ui->pushButton_2->setPalette(p1);
    ui->pushButton_3->setIcon(QPixmap("./picture/bone_AK47.png"));
    ui->pushButton_3->setIconSize(QSize(200,200));
    ui->pushButton_3->setPalette(p1);
}

SelectWindow::~SelectWindow()
{
    delete ui;
}

void SelectWindow::on_pushButton_pressed()
{
    ui->pushButton_2->setPalette(p1);
    ui->pushButton_3->setPalette(p1);
    ui->pushButton->setPalette(p2);
    setResult(1);
}

void SelectWindow::on_pushButton_2_pressed()
{
    ui->pushButton->setPalette(p1);
    ui->pushButton_3->setPalette(p1);
    ui->pushButton_2->setPalette(p2);
    setResult(2);
}


void SelectWindow::on_pushButton_3_pressed()
{
    ui->pushButton->setPalette(p1);
    ui->pushButton_2->setPalette(p1);
    ui->pushButton_3->setPalette(p2);
    setResult(3);
}

void SelectWindow::on_backButton_clicked()
{
    done(0);
}

void SelectWindow::on_nextButton_clicked()
{
    if(result() != 0)
        done(result());
}
void SelectWindow::startText(){
    ui->nextButton->setText("Start");
}
