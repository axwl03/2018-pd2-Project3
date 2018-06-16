#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(int p1_ID, QWidget *parent) :
    ui(new Ui::MainWindow),up(0), down(0), left(0), right(0), s(0), skillStatus(0), stage(4), waveStatus(0), score(0), respawnTime(0), skillTime(0), mode(1)
{
    widget = parent;
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 800, 1000);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QPixmap("./picture/ground.png")));
    p = new Player(100, p1_ID);
    p2 = new Enemy(100, 0, 1);//not using it
    scene->addItem(p);
    scene->addItem(p->w);
    p->setPos(500, 400);
    scene->addItem(p->healthbar);
    //set HP
    healthScene = new QGraphicsScene(0, 0, 140, 320);
    ui->graphicsView_2->setScene(healthScene);
    for(int i = 0; i < 3; ++i){
        hp.push_back(new QGraphicsPixmapItem(QPixmap("./picture/heart.png").scaled(40,40)));
        hp[i]->setPos(50*i, 0);
        healthScene->addItem(hp[i]);
    }
    for(int i = 0; i < 3; ++i){
        mp.push_back(new QGraphicsRectItem(0+50*i, 160, 30, 5));
        mp[i]->setBrush(QColor(67,156,204));
        healthScene->addItem(mp[i]);
    }
    qsrand(QDateTime::currentMSecsSinceEpoch());
    shield.push_back(new QGraphicsPixmapItem(QPixmap("./picture/shield.png")));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::player_action);
    timer->start(10);
    connect(timer, &QTimer::timeout, this, &MainWindow::check_health);
    wave();
    p2->setEnabled(0);
}
MainWindow::MainWindow(int p1_ID, int p2_ID, QWidget *parent):ui(new Ui::MainWindow),up(0),down(0),left(0),right(0),s(0),skillStatus(0),
    up2(0),down2(0),left2(0),right2(0),s2(0),stage(1),score(0),respawnTime(0),respawnTime2(0),mode(2)
{
    widget = parent;
    ui->setupUi(this);
    ui->label->setText("Kill: ");
    ui->label->setGeometry(870, 50, 160, 60);
    ui->label_2->setText("Kill: ");
    ui->label_2->setGeometry(870, 800, 160, 60);
    ui->label_3->setText("");
    ui->label_4->setText("");
    ui->lcdNumber->setGeometry(920, 50, 120, 60);
    ui->lcdNumber_2->setGeometry(920, 800, 120, 60);
    scene = new QGraphicsScene(0, 0, 800, 1000);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QPixmap("./picture/ground.png")));
    p = new Player(100, p1_ID);
    p2 = new Enemy(100, p2_ID, 1);
    scene->addItem(p);
    scene->addItem(p->w);
    p->setPos(500, 400);
    scene->addItem(p->healthbar);
    scene->addItem(p2);
    scene->addItem(p2->w);
    p2->setPos(250, 200);
    scene->addItem(p2->healthbar);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::player_action);
    timer->start(10);
    connect(timer, &QTimer::timeout, this, &MainWindow::check_health);
    ui->graphicsView->installEventFilter(this);
}
MainWindow::MainWindow(int p1_ID, int p2_ID, bool s, QWidget *parent):ui(new Ui::MainWindow),up(0),down(0),left(0),right(0),s(0),skillStatus(0),
    up2(0),down2(0),left2(0),right2(0),s2(0),skillStatus2(0),stage(1),waveStatus(0),score(0),respawnTime(0),respawnTime2(0),skillTime(0), skillTime2(0),mode(3)
{
   widget = parent;
   ui->setupUi(this);
   scene = new QGraphicsScene(0, 0, 800, 1000);
   ui->graphicsView->setScene(scene);
   scene->setBackgroundBrush(QBrush(QPixmap("./picture/ground.png")));
   p = new Player(100, p1_ID);
   p2 = new Player(100, p2_ID);
   scene->addItem(p);
   scene->addItem(p->w);
   p->setPos(500, 400);
   scene->addItem(p->healthbar);
   scene->addItem(p2);
   scene->addItem(p2->w);
   p2->setPos(250, 400);
   scene->addItem(p2->healthbar);
   healthScene = new QGraphicsScene(0, 0, 230, 320);
   ui->graphicsView_2->setScene(healthScene);
   for(int i = 0; i < 5; ++i){
       hp.push_back(new QGraphicsPixmapItem(QPixmap("./picture/heart.png").scaled(40,40)));
       hp[i]->setPos(50*i, 0);
       healthScene->addItem(hp[i]);
   }
   for(int i = 0; i < 5; ++i){
       mp.push_back(new QGraphicsRectItem(0+50*i, 160, 30, 5));
       mp[i]->setBrush(QColor(67,156,204));
       healthScene->addItem(mp[i]);
   }
   qsrand(QDateTime::currentMSecsSinceEpoch());
   for(int i = 0 ;i < 2; ++i)
       shield.push_back(new QGraphicsPixmapItem(QPixmap("./picture/shield.png")));
   timer = new QTimer(this);
   connect(timer, &QTimer::timeout, this, &MainWindow::player_action);
   timer->start(10);
   connect(timer, &QTimer::timeout, this, &MainWindow::check_health);
   ui->graphicsView->installEventFilter(this);
   wave();
}
MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->graphicsView && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down || keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_Right) {
            this->keyPressEvent(keyEvent);
            return true;
        }
    }
    return false;
}
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(p->scene() != 0){
        if(event->key() == Qt::Key_W)
            up = 1;
        if(event->key() == Qt::Key_A)
            left = 1;
        if(event->key() == Qt::Key_S)
            down = 1;
        if(event->key() == Qt::Key_D)
            right = 1;
        if(event->key() == Qt::Key_Space)
            if(respawnTime == 0) //could not shoot while respawning
                s = 1;
        if(event->key() == Qt::Key_F){
            scene->removeItem(p->w);
            p->changeWeapon();
            p->setItemPos();
            scene->addItem(p->w);
        }
        if(event->key() == Qt::Key_G && (mode == 1 || mode == 3))
            skill();
    }

    if(p2->isEnabled()){
        if(p2->scene() != 0){
            switch(event->key()){
            case Qt::Key_Up:
                up2 = 1;
                break;
            case Qt::Key_Left:
                left2 = 1;
                break;
            case Qt::Key_Down:
                down2 = 1;
                break;
            case Qt::Key_Right:
                right2 = 1;
                break;
            case Qt::Key_1:
                if(respawnTime2 == 0) //could not shoot while respawning
                    s2 = 1;
                break;
            case Qt::Key_2:
                scene->removeItem(p2->w);
                p2->changeWeapon();
                p2->setItemPos();
                scene->addItem(p2->w);
                break;
            case Qt::Key_3:
                if(mode != 2)
                    skill2();
                break;
            }
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
    case Qt::Key_Up:
        up2 = 0;
        break;
    case Qt::Key_Left:
        left2 = 0;
        break;
    case Qt::Key_Down:
        down2 = 0;
        break;
    case Qt::Key_Right:
        right2 = 0;
        break;
    case Qt::Key_1:
        s2 = 0;
        break;
    }
}
void MainWindow::player_action(){
    int d = 2.5;
    if(p->scene() != 0){
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
    if(p2->isEnabled()){
        if(p2->scene() != 0 && mode == 2){
            if(p2->timeInterval < 100)
                ++p2->timeInterval;
            if(up2 == 1 && p2->y() >= p2->pixmap().height()*p2->scale())
                p2->setPos(p2->x(), p2->y()-d);
            if(down2 == 1 && p2->y() < 500)
                p2->setPos(p2->x(), p2->y()+d);
            if(left2 == 1 && p2->x()-p2->pixmap().width()*p2->scale() >= 0)
                p2->setPos(p2->x()-d, p2->y());
            if(right2 == 1 && p2->x() <= 800)
                p2->setPos(p2->x()+d, p2->y());
            if(s2 == 1 && p2->timeInterval >= p2->w->shot_interval && respawnTime2 == 0){
                p2->timeInterval = 0;
                shoot(*p2->w);
            }p2->setItemPos();
        }else if(p2->scene() != 0 && mode == 3){
            if(p2->timeInterval < 100)
                ++p2->timeInterval;
            if(up2 == 1 && p2->y() >= 500)
                p2->setPos(p2->x(), p2->y()-d);
            if(down2 == 1 && p2->y()+p2->pixmap().height()*p2->scale() <= 1000)
                p2->setPos(p2->x(), p2->y()+d);
            if(left2 == 1 && p2->x() >= 0)
                p2->setPos(p2->x()-d, p2->y());
            if(right2 == 1 && p2->x()+p2->pixmap().width()*p2->scale() <= 800)
                p2->setPos(p2->x()+d, p2->y());
            if(s2 == 1 && p2->timeInterval >= p2->w->shot_interval && respawnTime2 == 0){
                p2->timeInterval = 0;
                shoot(*p2->w);
            }p2->setItemPos();
        }
    }
}
void MainWindow::shoot(weapon &w){
    //shotgun bullet
    if(w.data(4).toString() == "shotgun"){
        w.sound.setPosition(0);
        w.sound.play();
        QVector<bullet *> sb(5);
        for(int i = 0; i < 5; ++i){
            sb[i] = new bullet(w.data(0).toInt(), w.data(1).toInt(), w.data(2).toInt());
            scene->addItem(sb[i]);
            if(w.data(0).toInt() > 0)
                sb[i]->setPos(w.x() + w.pixmap().width()*w.scale()/2 - sb[i]->pixmap().width()*sb[i]->scale()/2, w.y()-sb[i]->pixmap().height()*sb[i]->scale());
            if(w.data(0).toInt() < 0)
                sb[i]->setPos(w.x() - w.pixmap().width()*w.scale()/2 - sb[i]->pixmap().width()*sb[i]->scale()/2, w.y());
        }
        sb[0]->flash.setScale(w.data(3).toFloat());
        scene->addItem(&sb[0]->flash);
        if(w.data(0).toInt() > 0)
            sb[0]->flash.setPos(w.x() + w.pixmap().width()*w.scale()/2 - sb[0]->flash.pixmap().width()*sb[0]->flash.scale()/2, w.y()-sb[0]->flash.pixmap().height()*sb[0]->flash.scale());
        if(w.data(0).toInt() < 0){
            sb[0]->flash.setRotation(180);
            sb[0]->flash.setPos(w.x() - w.pixmap().width()*w.scale()/2 + sb[0]->flash.pixmap().width()*sb[0]->flash.scale()/2, w.y()+sb[0]->flash.pixmap().height()*sb[0]->flash.scale());
        }
        for(int i = 0; i < 5; ++i)
            connect(timer, &QTimer::timeout, sb[i], &bullet::fly);
        return;
    }
    //normal bullet
    bullet *b = new bullet(w.data(0).toInt(), w.data(1).toInt(), w.data(2).toInt());
    w.sound.setPosition(0);
    w.sound.play();
    b->flash.setScale(w.data(3).toFloat());
    scene->addItem(b);
    scene->addItem(&b->flash);
    if(w.data(0).toInt() > 0){
        b->setPos(w.x() + w.pixmap().width()*w.scale()/2 - b->pixmap().width()*b->scale()/2, w.y()-b->pixmap().height()*b->scale());
        b->flash.setPos(w.x() + w.pixmap().width()*w.scale()/2 - b->flash.pixmap().width()*b->flash.scale()/2, w.y()-b->flash.pixmap().height()*b->flash.scale());
    }
    if(w.data(0).toInt() < 0){
        b->setPos(w.x() - w.pixmap().width()*w.scale()/2 - b->pixmap().width()*b->scale()/2, w.y());
        b->flash.setRotation(180);
        b->flash.setPos(w.x() - w.pixmap().width()*w.scale()/2 + b->flash.pixmap().width()*b->flash.scale()/2, w.y()+b->flash.pixmap().height()*b->flash.scale());
    }
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
            if((mode == 1 || mode == 3) && hp.size() > 0){
                healthScene->removeItem(hp.last());
                delete hp.last();
                hp.removeLast();
                if(hp.size() != 0)
                    ++respawnTime;
                if(hp.size() == 0){
                    if(mode == 1)
                        message(0);
                }
            }
            if(mode == 3 && hp.size() == 0 && respawnTime == 0 && respawnTime2 == 0)
                if(p2->scene() == 0)
                    message(0);
            if(mode == 2 && ui->lcdNumber->intValue() < 10){
                ui->lcdNumber->display(QString::number(ui->lcdNumber->intValue()+1));
                if(ui->lcdNumber->intValue() == 10)
                    message(0);
                ++respawnTime;
            }
        }
    }
    if(respawnTime != 0){
        ++respawnTime;
        if(respawnTime == 300){
            scene->addItem(p);
            scene->addItem(p->w);
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
                scene->addItem(p->healthbar);
                p->setData(1, false);
                p->setData(2, 0);
            }
        }
    }
    if(p2->isEnabled()){
        if(p2->scene() != 0 && respawnTime2 == 0){
            if(p2->data(1).toInt() == 1 && p2->health > 0){
                p2->damaged(p2->data(2).toInt());
                p2->setData(1, false);
                p2->setData(2, 0);
            }
            if(p2->health <= 0){
                scene->removeItem(p2);
                scene->removeItem(p2->w);
                scene->removeItem(p2->healthbar);
                if((mode == 1 || mode == 3) && hp.size() > 0){
                    healthScene->removeItem(hp.last());
                    delete hp.last();
                    hp.removeLast();
                    if(hp.size() != 0)
                        ++respawnTime2;
                    if(hp.size() == 0){
                        if(mode == 1)
                            message(0);
                    }
                }
                if(mode == 3 && hp.size() == 0 && respawnTime == 0 && respawnTime2 == 0)
                    if(p->scene() == 0)
                        message(0);
                if(mode == 2 && ui->lcdNumber_2->intValue() < 10){
                    ui->lcdNumber_2->display(QString::number(ui->lcdNumber_2->intValue()+1));
                    if(ui->lcdNumber_2->intValue() == 10)
                        message(1);
                    ++respawnTime2;
                }
            }
        }
        if(respawnTime2 != 0){
            ++respawnTime2;
            if(respawnTime2 == 300){
                scene->addItem(p2);
                scene->addItem(p2->w);
            }
            if(respawnTime2 == 330 || respawnTime2 == 390 || respawnTime2 == 450){
                p2->setVisible(0);
                p2->w->setVisible(0);
            }
            if(respawnTime2 == 360 || respawnTime2 == 420 || respawnTime2 == 480){
                p2->setVisible(1);
                p2->w->setVisible(1);
                if(respawnTime2 == 480){
                    respawnTime2 = 0;
                    p2->health = 100;
                    scene->addItem(p2->healthbar);
                    p2->setData(1, false);
                    p2->setData(2, 0);
                }
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
            if(e[i]->timeInterval >= e[i]->w->shot_interval && p2->isEnabled() && (e[i]->w->x()-p2->w->x() < 50 && e[i]->w->x()-p2->w->x() >-50)){
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
    if(mode == 1 && e.size() == 0 && stage <= 5){
        ++stage;
        wave();
    }
    if(mode == 1 && stage > 5)
        message(1);
    if(mode == 3 && e.size() == 0 && stage <= 6){
        ++stage;
        wave();
    }
    if(mode == 3&& stage > 6)
        message(1);
}
void MainWindow::wave(){
    for(int i = 0; i < stage; ++i){
        e.push_back(new Enemy(100, 2));
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
void MainWindow::skill(){
    ++skillTime;
    if(mp.size() != 0){
        if(skillStatus == 0){
            shield[0]->setData(0, "shield");
            scene->addItem(shield[0]);
            connect(timer, &QTimer::timeout, this, &MainWindow::skill);
            skillStatus = 1;
            healthScene->removeItem(mp.last());
            mp.removeLast();
        }
    }
    ui->label_5->setText(QString::number((int)(500-skillTime)/100));
    shield[0]->setPos(p->x()+p->pixmap().width()*p->scale()/2-shield[0]->pixmap().width()/2, p->y()-150);
    if(skillTime >= 500)
        ui->label_5->setText("");
    if(skillTime > 500){
        skillStatus = 0;
        skillTime = 0;
        scene->removeItem(shield[0]);
        disconnect(timer, &QTimer::timeout, this, &MainWindow::skill);
    }
}
void MainWindow::skill2(){
    ++skillTime2;
    if(mp.size() != 0){
        if(skillStatus2 == 0){
            shield[1]->setData(0, "shield");
            scene->addItem(shield[1]);
            connect(timer, &QTimer::timeout, this, &MainWindow::skill2);
            skillStatus2 = 1;
            healthScene->removeItem(mp.last());
            mp.removeLast();
        }
    }
    ui->label_5->setText(QString::number((int)(500-skillTime2)/100));
    shield[1]->setPos(p2->x()+p2->pixmap().width()*p2->scale()/2-shield[1]->pixmap().width()/2, p2->y()-150);
    if(skillTime2 >= 500)
        ui->label_5->setText("");
    if(skillTime2 > 500){
        skillStatus2 = 0;
        skillTime2 = 0;
        scene->removeItem(shield[1]);
        disconnect(timer, &QTimer::timeout, this, &MainWindow::skill2);
    }
}
void MainWindow::closeEvent(QCloseEvent *event){
    event->accept();
    widget->show();
    delete this;
}
void MainWindow::message(bool result){
    QMessageBox msgBox;
    msgBox.addButton("Menu", QMessageBox::AcceptRole)->setFlat(1);
    msgBox.addButton("Exit", QMessageBox::RejectRole)->setFlat(1);
    QPalette p;
    p.setBrush(QPalette::Window, QBrush(QColor(55,65,71)));
    p.setBrush(QPalette::Button, QBrush(QColor(55,65,71)));
    p.setBrush(QPalette::WindowText, QBrush(QColor(124,176,176)));
    p.setBrush(QPalette::ButtonText, QBrush(QColor(124,176,176)));
    msgBox.setPalette(p);
    QString str = "Your score is ";
    str.append(QString::number(ui->lcdNumber->intValue()));
    str.append("\n");
    if((mode == 1 || mode == 3) && result == 0){
        msgBox.setText("You are dead");
        msgBox.setInformativeText(str);
        saveScore(ui->lcdNumber->intValue());
    }
    if((mode == 1 || mode == 3) && result == 1){
        msgBox.setText("You Win!!!");
        msgBox.setInformativeText(str);
        saveScore(ui->lcdNumber->intValue());
    }
    if(mode == 2 && result == 1){
        msgBox.setText("Player1 Win!!");
    }
    if(mode == 2 && result == 0){
        msgBox.setText("Player2 Win!!");
    }
    msgBox.exec();
    if(msgBox.clickedButton()->text() == "Exit")
        exit(0);
    if(msgBox.clickedButton()->text() == "Menu")
        close();
}
void MainWindow::saveScore(int t){
    QFile myfile("rank");
    if (!myfile.open(QIODevice::Append))
        QMessageBox::warning(this, "Oops!", "file not open");
    QTextStream output(&myfile);
    output << QString::number(t);
    output << "\n";
    myfile.close();
}
