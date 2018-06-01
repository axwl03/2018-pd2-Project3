#include "bullet.h"

bullet::bullet(int s, int d, int de, QObject *parent) : QObject(parent)
{
    speed = s;
    damage = d;
    if(de != 0){
        if(qrand()%2 == 0)
            deviation = (float)(qrand()%(10*de))/10;
        if(qrand()%2 ==  1)
            deviation = -(float)(qrand()%(10*de))/10;

    }
    setPixmap(QPixmap("./picture/bullet.png"));
    setScale(0.3);
}
void bullet::fly(){
    setPos(x()+deviation, y()-speed);
    for(int i = 0; i < scene()->items().size(); ++i){
        if(scene()->items().at(i) == this)
            continue;
        if(isHit(*(scene()->items().at(i)))){
            qDebug() << pos()<< scene()->items().at(i) << "hit";
            scene()->items().at(i)->setData(1, true);//being hit
            scene()->items().at(i)->setData(2, damage);//set damage
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    if(y()<-100 || y()>1100){
        scene()->removeItem(this);
        delete this;
    }
}
bool bullet::isHit(const QGraphicsItem &human){
    int bx = x() + pixmap().width() * scale() / 2; //center position x of bullet
    int by = y() + pixmap().height() * scale() / 2; //center position y of bullet
    int w = human.boundingRect().width() * human.scale(); //human's width
    int h = human.boundingRect().height() * human.scale();  //human's height
    if(human.data(0).toString() == "enemy"){
        if(bx >= human.pos().x() - w && bx <= human.pos().x() && by <= human.pos().y() && by >= human.pos().y() - h)
            return true;
        else return false;
    }
    if(human.data(0).toString() == "p1"){
        if(bx >= human.pos().x() && bx <= human.pos().x() + w && by >= human.pos().y() && by <= human.pos().y() + h)
            return true;
        else return false;
    }
    return false;
}
