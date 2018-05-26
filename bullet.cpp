#include "bullet.h"

bullet::bullet(int s, int d, QObject *parent) : QObject(parent)
{
    speed = s;
    damage = d;
}

void bullet::fly(){
    setPos(x(), y()-speed);
    int w = 0, h = 0;
    for(int i = 0; i < scene()->items().size(); ++i){
        if(scene()->items().at(i) == this)
            continue;
        w = scene()->items().at(i)->boundingRect().width() * scene()->items().at(i)->scale();
        h = scene()->items().at(i)->boundingRect().width() * scene()->items().at(i)->scale();
        if(x()+pixmap().width()*scale()/2 >= scene()->items().at(i)->pos().x() && x()+pixmap().width()*scale()/2 <= scene()->items().at(i)->pos().x()+w
                && y()+pixmap().height()*scale()/2 >= scene()->items().at(i)->pos().y() && y()+pixmap().height()*scale()/2 <= scene()->items().at(i)->pos().y()+h){
            qDebug() << pos()<< scene()->items().at(i) << "hit";
            scene()->items().at(i)->setData(0, true);//being hit
            scene()->items().at(i)->setData(1, damage);//set damage
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    if(y()<0){
        scene()->removeItem(this);
        delete this;
    }
}
