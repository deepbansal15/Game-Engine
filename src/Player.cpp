/*
 * Player.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: nathan
 */

#include "Player.h"
#include "InputManager.h"

namespace TileEngine
{

Player::Player(std::string filename, int x, int y) : MovingEntity(filename, x, y, 3)
{
}

Player::~Player()
{
	ImageManagerInst->releaseSurface(image);
}
void Player::update()
{
    MovingEntity::update();
}

void Player::handleEvents()
{
    float accel = .5;
    if( InputInst->keyHeld(SDLK_LEFT))
    {
        acceleration.X = -accel;
    }
    else if( InputInst->keyReleased(SDLK_LEFT))
    {
        acceleration.X = 0;
    }
    if( InputInst->keyHeld(SDLK_RIGHT))
    {
        acceleration.X = accel;
    }
    else if( InputInst->keyReleased(SDLK_RIGHT))
    {
        acceleration.X = 0;
    }
    
    if( InputInst->keyHeld(SDLK_UP))
    {
        acceleration.Y = -accel;
    }
    else if( InputInst->keyReleased(SDLK_UP))
    {
        acceleration.Y = 0;
    }
    if( InputInst->keyHeld(SDLK_DOWN))
    {
        acceleration.Y = accel;
    }
    else if( InputInst->keyReleased(SDLK_DOWN))
    {
        acceleration.Y = 0;
    }
}
void Player::processCollision(const Entity* entity)
{
}
}
