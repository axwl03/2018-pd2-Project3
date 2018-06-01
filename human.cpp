#include "human.h"

Human::Human(int h, QObject *parent) : QObject(parent), health(h), timeInterval(0)
{
}
void Human::damaged(int damage){
    health -= damage;
}
