#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "MovingEntity.h"

class Enemy : public MovingEntity
{
public:
    Enemy(std::string filename, int x, int y) : 
        MovingEntity(filename, x, y , 3){}

    virtual void update();
    virtual void handleEvents();
    virtual void processCollision(const Entity* entity);
};

#endif
