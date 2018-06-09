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
    explicit MainWindow(int p1_ID);
    MainWindow(int p1_ID, int p2_ID);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void player_action();
    void shoot(weapon &w);
    void check_health();
    void enemy_move();
    void wave();
    void skill();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene, *healthScene;
    Human *p;
    bool up, down, left, right, s, skillStatus;
    bool up2, down2, left2, right2, s2, skillStatus2;
    int stage, waveStatus, score, respawnTime, respawnTime2, skillTime, mode;
    QVector<Human*> e;
    QVector<QGraphicsPixmapItem*> hp;
    QVector<QGraphicsRectItem*> mp;
    Human *p2;
    QTimer *timer;
};

#endif // MAINWINDOW_H
