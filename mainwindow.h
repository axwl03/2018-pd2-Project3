#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include "bullet.h"
#include <QDebug>
#include "player.h"
#include "weapon.h"
#include <QGraphicsScene>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void player_action();
    void shoot(const weapon &w);
    void check_health();
    void enemy_move();
    void update_rand();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    player *p;
    static bool up, down, left, right, s;
    int shot_interval, time, t1, t2;
    QVector<player*> e;
    QTimer *timer;
    QMediaPlayer sound;
};

#endif // MAINWINDOW_H
