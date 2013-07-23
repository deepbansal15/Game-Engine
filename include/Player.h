/*
 * Player.h
 *
 *      Author: nathan
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"
#include "ImageManager.h"
#include "InputManager.h"
#include "MovingEntity.h"
namespace TileEngine
{
class Player: public MovingEntity
{
public:
	Player(std::string filename, int x, int y);
	virtual ~Player();

	virtual void update();
	virtual void handleEvents();
	virtual void processCollision(const Entity* entity);

protected:

};
}

#endif /* MOVINGENTITY_H_ */
