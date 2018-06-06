#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include "bullet.h"
#include "player.h"
#include "weapon.h"
#include "enemy.h"
#include "human.h"
#include <QMessageBox>

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
    void shoot(weapon &w);
    void check_health();
    void enemy_move();
    void wave();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene, *healthScene;
    Player *p;
    static bool up, down, left, right, s;
    int shot_interval, stage, waveStatus, score, respawnTime;
    QVector<Enemy*> e;
    QVector<QGraphicsPixmapItem*> hp;
    QTimer *timer;
};

#endif // MAINWINDOW_H
