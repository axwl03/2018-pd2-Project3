#ifndef RANK_H
#define RANK_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
#include <QPushButton>

namespace Ui {
class rank;
}

class rank : public QMainWindow
{
    Q_OBJECT

public:
    explicit rank(QWidget *parent = 0);
    ~rank();
    void display();
    void closeEvent(QCloseEvent *event);

private:
    Ui::rank *ui;
    QVector<int> score;
    QWidget *widget;
};

#endif // RANK_H
