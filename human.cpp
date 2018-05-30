#include "human.h"

Human::Human(QObject *parent) : QObject(parent)
{
}
void Human::damaged(int damage){
    health -= damage;
}
