#include "selectwindow.h"
#include "ui_selectwindow.h"

SelectWindow::SelectWindow(QString str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectWindow)
{
    if(parent != NULL)
        parent->close();
    QPalette palette;
    palette.setColor(QPalette::Light, Qt::lightGray);
    palette.setColor(QPalette::Dark, QColor(255,255,255, 255));

    ui->setupUi(this);
    ui->label->setText(str);
    ui->pushButton->setIcon(QPixmap("./picture/killer_AWM.png"));
    ui->pushButton->setIconSize(QSize(200,200));
    ui->pushButton->setPalette(palette);
    ui->pushButton_2->setIcon(QPixmap("./picture/officer_shotgun.png"));
    ui->pushButton_2->setIconSize(QSize(200,200));
    ui->pushButton_2->setPalette(palette);
    ui->pushButton_3->setIcon(QPixmap("./picture/bone_AK47.png"));
    ui->pushButton_3->setIconSize(QSize(200,200));
    ui->pushButton_3->setPalette(palette);
}

SelectWindow::~SelectWindow()
{
    delete ui;
}

void SelectWindow::on_pushButton_pressed()
{
    ui->pushButton_2->setBackgroundRole(QPalette::Light);
    ui->pushButton_3->setBackgroundRole(QPalette::Light);
    ui->pushButton->setBackgroundRole(QPalette::Dark);
    setResult(1);
}

void SelectWindow::on_pushButton_2_pressed()
{
    ui->pushButton->setBackgroundRole(QPalette::Light);
    ui->pushButton_3->setBackgroundRole(QPalette::Light);
    ui->pushButton_2->setBackgroundRole(QPalette::Dark);
    setResult(2);
}


void SelectWindow::on_pushButton_3_pressed()
{
    ui->pushButton->setBackgroundRole(QPalette::Light);
    ui->pushButton_2->setBackgroundRole(QPalette::Light);
    ui->pushButton_3->setBackgroundRole(QPalette::Dark);
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
