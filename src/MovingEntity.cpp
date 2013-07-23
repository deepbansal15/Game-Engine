/*
 * MovingEntity.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: nathan
 */

#include "MovingEntity.h"

#define FRICTION .94

namespace TileEngine
{

MovingEntity::MovingEntity(std::string filename, int x, int y, float maxSpeed)
{
    position.X = x;
    position.Y = y;
    this->maxSpeed = maxSpeed;
	image = ImageManagerInst->acquireSurface(filename);
}

MovingEntity::~MovingEntity()
{
	ImageManagerInst->releaseSurface(image);
}

void MovingEntity::update()
{
    velocity += acceleration;
    velocity *= FRICTION;
    capVelocity();
	position += velocity;
}

void MovingEntity::handleEvents()
{
}
void MovingEntity::processCollision(const Entity* entity)
{

}

void MovingEntity::capVelocity()
{
    bool xPos = velocity.X > 0;
    bool yPos = velocity.Y > 0;


    if(abs(velocity.X) > maxSpeed)
    {
        velocity.X = (xPos) ? maxSpeed : -maxSpeed;
    }
    if(abs(velocity.Y) > maxSpeed)
    {
        velocity.Y = (yPos) ? maxSpeed : -maxSpeed;
    }
}
}
