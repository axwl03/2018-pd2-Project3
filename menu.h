#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QMessageBox>
#include "rank.h"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Menu *ui;
    rank *score;
};

#endif // MENU_H
