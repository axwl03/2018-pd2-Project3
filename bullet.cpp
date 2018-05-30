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
    int w = 0, h = 0;
    for(int i = 0; i < scene()->items().size(); ++i){
        if(scene()->items().at(i) == this)
            continue;
        w = scene()->items().at(i)->boundingRect().width() * scene()->items().at(i)->scale();
        h = scene()->items().at(i)->boundingRect().width() * scene()->items().at(i)->scale();
        if(x()+pixmap().width()*scale()/2 >= scene()->items().at(i)->pos().x() && x()+pixmap().width()*scale()/2 <= scene()->items().at(i)->pos().x()+w
                && y()+pixmap().height()*scale()/2 >= scene()->items().at(i)->pos().y() && y()+pixmap().height()*scale()/2 <= scene()->items().at(i)->pos().y()+h
                && scene()->items().at(i)->data(0).toString() == "enemy"){
            qDebug() << pos()<< scene()->items().at(i) << "hit";
            scene()->items().at(i)->setData(1, true);//being hit
            scene()->items().at(i)->setData(2, damage);//set damage
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    if(y()<-100){
        scene()->removeItem(this);
        delete this;
    }
}
