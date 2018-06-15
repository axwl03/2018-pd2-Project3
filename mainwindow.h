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
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int p1_ID, QWidget *parent);
    MainWindow(int p1_ID, int p2_ID, QWidget *parent);
    MainWindow(int p1_ID, int p2_ID, bool s, QWidget *parent);
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
    void skill2();
    void closeEvent(QCloseEvent *event);
    void message(bool result);
    void saveScore(int t);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene, *healthScene;
    Human *p, *p2;
    bool up, down, left, right, s, skillStatus;
    bool up2, down2, left2, right2, s2, skillStatus2;
    int stage, waveStatus, score, respawnTime, respawnTime2, skillTime, skillTime2, mode;
    QVector<Human*> e;
    QVector<QGraphicsPixmapItem*> hp;
    QVector<QGraphicsRectItem*> mp;
    QVector<QGraphicsPixmapItem*> shield;
    QTimer *timer;
    QWidget *widget;
};

#endif // MAINWINDOW_H
