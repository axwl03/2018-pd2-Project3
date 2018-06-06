#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), stage(1), waveStatus(0), score(0), respawnTime(0)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 800, 1000);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::lightGray);
    p = new Player(100, 0);
    scene->addItem(p);
    scene->addItem(p->w);
    p->setPos(500, 400);   //<--
    p->setData(0, "p1");
    scene->addItem(p->healthbar);
    //set HP
    healthScene = new QGraphicsScene(0, 0, 140, 100);
    ui->graphicsView_2->setScene(healthScene);
    for(int i = 0; i < 3; ++i){
        hp.push_back(new QGraphicsPixmapItem(QPixmap("./picture/heart.png").scaled(40,40)));
        hp[i]->setPos(50*i, 0);
        healthScene->addItem(hp[i]);
    }
    qsrand(QDateTime::currentMSecsSinceEpoch());
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::player_action);
    timer->start(10);
    shot_interval = 100;
    connect(timer, &QTimer::timeout, this, &MainWindow::check_health);
    wave();
}
MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::up = 0, MainWindow::down = 0, MainWindow::left = 0, MainWindow::right = 0, MainWindow::s = 0;
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(p->scene() != 0){
        switch(event->key()){
        case Qt::Key_W:
            up = 1;
            break;
        case Qt::Key_A:
            left = 1;
            break;
        case Qt::Key_S:
            down = 1;
            break;
        case Qt::Key_D:
            right = 1;
            break;
        case Qt::Key_Space:
            if(respawnTime == 0) //could not shoot while respawning
                s = 1;
            break;
        case Qt::Key_F:
            scene->removeItem(p->w);
            p->changeWeapon();
            p->setItemPos();
            scene->addItem(p->w);
        }
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_W:
        up = 0;
        break;
    case Qt::Key_A:
        left = 0;
        break;
    case Qt::Key_S:
        down = 0;
        break;
    case Qt::Key_D:
        right = 0;
        break;
    case Qt::Key_Space:
        s = 0;
        break;
    }
}
void MainWindow::player_action(){
    int d = 2.5;
    if(p->timeInterval < 100)
        ++p->timeInterval;
    if(up == 1 && p->y() >= 500)
        p->setPos(p->x(), p->y()-d);
    if(down == 1 && p->y()+p->pixmap().height()*p->scale() <= 1000)
        p->setPos(p->x(), p->y()+d);
    if(left == 1 && p->x() >= 0)
        p->setPos(p->x()-d, p->y());
    if(right == 1 && p->x()+p->pixmap().width()*p->scale() <= 800)
        p->setPos(p->x()+d, p->y());
    if(s == 1 && p->timeInterval >= p->w->shot_interval && respawnTime == 0){
        p->timeInterval = 0;
        shoot(*p->w);
    }
    p->setItemPos();
}
void MainWindow::shoot(weapon &w){
    bullet *b = new bullet(w.data(0).toInt(), w.data(1).toInt(), w.data(2).toInt());
    w.sound.setPosition(0);
    w.sound.play();
    scene->addItem(b);
    if(w.data(0).toInt() > 0)
        b->setPos(w.x() + w.pixmap().width()*w.scale()/2 - b->pixmap().width()*b->scale()/2, w.y()-b->pixmap().height()*b->scale());
    if(w.data(0).toInt() < 0)
        b->setPos(w.x() - w.pixmap().width()*w.scale()/2 - b->pixmap().width()*b->scale()/2, w.y()+b->pixmap().height()*b->scale());
    b->connect(timer, &QTimer::timeout, b, &bullet::fly);
}
void MainWindow::check_health(){
    for(int i = 0; i < e.size(); ++i){
        if(e[i]->data(1).toInt() == 1){ 
            e[i]->damaged(e[i]->data(2).toInt());
            score += e[i]->data(2).toInt();
            ui->lcdNumber->display(score);
            e[i]->setData(1, false);
            e[i]->setData(2, 0);
        }
    }
    if(p->scene() != 0 && respawnTime == 0){
        if(p->data(1).toInt() == 1 && p->health > 0){
            p->damaged(p->data(2).toInt());
            p->setData(1, false);
            p->setData(2, 0);
        }
        if(p->health <= 0){
            scene->removeItem(p);
            scene->removeItem(p->w);
            scene->removeItem(p->healthbar);
            if(hp.size() > 0){
                healthScene->removeItem(hp.last());
                delete hp.last();
                hp.removeLast();
                if(hp.size() != 0)
                    ++respawnTime;
                if(hp.size() == 0){
                    QMessageBox::information(this, "Oops!!", "You lose!!");
                }
            }
        }
    }
    if(respawnTime != 0){
        ++respawnTime;
        if(respawnTime == 300){
            scene->addItem(p);
            scene->addItem(p->w);
            scene->addItem(p->healthbar);
        }
        if(respawnTime == 330 || respawnTime == 390 || respawnTime == 450){
            p->setVisible(0);
            p->w->setVisible(0);
        }
        if(respawnTime == 360 || respawnTime == 420 || respawnTime == 480){
            p->setVisible(1);
            p->w->setVisible(1);
            if(respawnTime == 480){
                respawnTime = 0;
                p->health = 100;
                p->setData(1, false);
                p->setData(2, 0);
            }
        }
    }
}
void MainWindow::enemy_move(){
    for(int i = 0; i < e.size(); ++i){
        ++e[i]->time;
        if(e[i]->time > 200){
            e[i]->time = 0;
            e[i]->setNewPosition();
        }
    }
    for(int i = 0; i < e.size(); ++i){
        ++e[i]->timeInterval;
        if(e[i]->health > 0){
            e[i]->move();
            e[i]->setItemPos();
            if(e[i]->timeInterval >= e[i]->w->shot_interval && (e[i]->w->x()-p->w->x() < 50 && e[i]->w->x()-p->w->x() >-50)){//enemy firing
                shoot(*e[i]->w);
                e[i]->timeInterval = 0;
            }
        }
        if(e[i]->health <= 0){
            scene->removeItem(e[i]);
            scene->removeItem(e[i]->w);
            scene->removeItem(e[i]->healthbar);
            delete e[i];
            e.remove(i);
        }
    }
    /*if(e.size() != 0){
        if(e[0]->health > 0)
            e[0]->move(p->x(), t2);
        if(e[0]->health <= 0){
            scene->removeItem(e[0]);
            e.remove(0);
        }
    }*/
    if(e.size() == 0 && stage < 5){
        ++stage;
        wave();
    }
}
void MainWindow::wave(){
    for(int i = 0; i < stage; ++i){
        e.push_back(new Enemy(100, 0));
        scene->addItem(e[i]);
        e[i]->setPos(qrand()%700+100, -100);
        scene->addItem(e[i]->w);
        scene->addItem(e[i]->healthbar);
        if(waveStatus == 0){
            connect(timer, &QTimer::timeout, this, &MainWindow::enemy_move);
            ++waveStatus;
        }
    }ui->lcdNumber_2->display(stage);
}
