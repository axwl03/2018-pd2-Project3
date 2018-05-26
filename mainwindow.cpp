#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 800, 1000);
    ui->graphicsView->setScene(scene);
    //scene->setBackgroundBrush(Qt::green);
    p = new player(0);
    w = new weapon(0); //<--
    scene->addItem(p);
    scene->addItem(w);
    p->setPos(500, 400);   //<--
    w->setPos(570, 300);    //<--

    e = new player(0);
    scene->addItem(e);
    e->setPos(200, 200);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::player_action);
    timer->start(10);
    shot_interval = 100;
    connect(timer, &QTimer::timeout, this, &MainWindow::check_health);
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
    if(shot_interval < 100)
        ++shot_interval;
    if(up == 1 && p->y() >= 500)
        p->setPos(p->x(), p->y()-d);
    if(down == 1 && p->y()+p->pixmap().height()*p->scale()/2 <= 1000)
        p->setPos(p->x(), p->y()+d);
    if(left == 1 && p->x() >= 0)
        p->setPos(p->x()-d, p->y());
    if(right == 1 && p->x()+p->pixmap().width()*p->scale()/2 <= 800)
        p->setPos(p->x()+d, p->y());
    if(s == 1 && shot_interval >= w->shot_interval){
        shot_interval = 0;
        shoot();
        if(w->weapon_ID == 0)
            s = 0;
    }
    w->setPos(p->x()+70, p->y()-100);
}
void MainWindow::shoot(){
    float scale = 0.2;
    bullet *b = new bullet(40, 50);
    b->setPixmap(QPixmap("./picture/bullet.png"));
    b->setScale(scale);
    scene->addItem(b);
    b->setPos(w->x() + w->pixmap().width() / 2 - b->pixmap().width()*scale/2, w->y()-b->pixmap().height()*scale);
    b->connect(timer, &QTimer::timeout, b, &bullet::fly);
}
void MainWindow::check_health(){
    for(int i = 0; i < 1; ++i){
        if(e->data(0).toInt() == 1){
            e->damaged(e->data(1).toInt());
            e->setData(0, false);
            e->setData(1, 0);
        }
    }
}
