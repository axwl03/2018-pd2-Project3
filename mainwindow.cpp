#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),time(500)
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
    //scene->addItem(p->healthbar);

    sound.setMedia(QUrl::fromLocalFile("/home/wesleylin/ShootingGame/sound/gun.mp3"));

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
        s = 1;
        break;
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
    int d = 3;
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
    if(s == 1 && p->timeInterval >= p->w->shot_interval){
        p->timeInterval = 0;
        shoot(*p->w);
    }
    p->setItemPos();
}
void MainWindow::shoot(const weapon &w){
    bullet *b = new bullet(w.data(0).toInt(), w.data(1).toInt(), w.data(2).toInt());
    sound.setPosition(20);
    sound.play();
    scene->addItem(b);
    b->setPos(w.x() + w.pixmap().width()*w.scale()/2 - b->pixmap().width()*b->scale()/2, w.y()-b->pixmap().height()*b->scale());
    b->connect(timer, &QTimer::timeout, b, &bullet::fly);
}
void MainWindow::check_health(){
    for(int i = 0; i < e.size(); ++i){
        if(e[i]->data(1).toInt() == 1){
            e[i]->damaged(e[0]->data(2).toInt());
            e[i]->setData(1, false);
            e[i]->setData(2, 0);
        }
    }/*if(p->data(1).toInt() == 1){
        p->damaged(p->data(2).toInt());
        p->setData(1, false);
        p->setData(2, 0);
    }*/
}
void MainWindow::enemy_move(){
    ++time;
    if(time > 200){
        time = 0;
        update_rand();
    }
    if(e.size() != 0){
        ++e[0]->timeInterval;
        if(e[0]->health > 0){
            e[0]->move(t1, t2);
            e[0]->setItemPos();
       /*     if(e[0]->timeInterval >= e[0]->w->shot_interval && time > 100){
                shoot(*e[0]->w);
                e[0]->timeInterval = 0;
            }*/
        }
        if(e[0]->health <= 0){
            scene->removeItem(e[0]);
            scene->removeItem(e[0]->w);
            scene->removeItem(e[0]->healthbar);
            e.remove(0);
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
}
void MainWindow::update_rand(){
    qsrand(QDateTime::currentMSecsSinceEpoch());
    t1 = qrand()%700+100;
    t2 = qrand()%100+200;
}
void MainWindow::wave(){
    e.push_back(new Enemy(100, 0));
    scene->addItem(e[0]);
    e[0]->setPos(200, -100);
    scene->addItem(e[0]->w);
    scene->addItem(e[0]->healthbar);
    e[0]->w->setData(0, -30);
    connect(timer, &QTimer::timeout, this, &MainWindow::enemy_move);
}
