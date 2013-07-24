/*
 * MovingEntity.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: nathan
 */

#include "MovingEntity.h"
#include "InputManager.h"

namespace TileEngine
{

const float MovingEntity::GRAVITY = 1;
MovingEntity::MovingEntity(std::string filename, int x, int y, int maxSpeed)
{
    acceleration.Y = GRAVITY;
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
    velocity.X *= .9;
    capVelocity();
	position += velocity;
}

void MovingEntity::handleEvents()
{
    if( InputInst->keyHeld(SDLK_LEFT))
    {
        acceleration.X = -1;
    }
    else if( InputInst->keyReleased(SDLK_LEFT))
    {
        acceleration.X = 0;
    }
    if( InputInst->keyHeld(SDLK_RIGHT))
    {
        acceleration.X = 1;
    }
    else if( InputInst->keyReleased(SDLK_RIGHT))
    {
        acceleration.X = 0;
    }
}
void MovingEntity::processCollision(const Entity* entity)
{

}

void MovingEntity::processCollision(const CollisionLayer *layer)
{
    Point current = convertPositionToCell(position + velocity);

    int topLeft = layer->getTile(current.X -1, current.Y -1);
    int top = layer->getTile(current.X, current.Y -1);
    int topRight = layer->getTile(current.X +1, current.Y -1);

    int left = layer->getTile(current.X -1, current.Y);
    int right = layer->getTile(current.X +1, current.Y);

    int bottomLeft = layer->getTile(current.X -1, current.Y +1);
    int bottom = layer->getTile(current.X, current.Y +1);
    int bottomRight = layer->getTile(current.X +1, current.Y +1);

    if(bottomLeft == 1 || bottom == 1 || bottomRight == 1)
    {
        velocity.Y = 0;
    }
}

void MovingEntity::capVelocity()
{
    velocity.X = ( velocity.X > maxSpeed ) ? maxSpeed : velocity.X;
    velocity.Y = ( velocity.Y > maxSpeed ) ? maxSpeed : velocity.Y;
}
}
