/*
 * MovingEntity.h
 *
 *  Created on: Jan 25, 2013
 *      Author: nathan
 */

#ifndef MOVINGENTITY_H_
#define MOVINGENTITY_H_

#include "Entity.h"
#include "ImageManager.h"
#include "InputManager.h"
#include "CollisionLayer.h"
#include <string>
#include "Window.h"
#include <cstdlib>
#include "Globals.h"

namespace TileEngine
{
class MovingEntity: public Entity
{
public:
	MovingEntity(std::string filename, int x, int y, int maxSpeed = 8);
	virtual ~MovingEntity();

	void update();
	void handleEvents();
	void processCollision(const Entity* entity);
    void processCollision(const CollisionLayer* layer);

protected:
	Vector2 velocity;
    Vector2 acceleration;

    float maxSpeed;

private:
    static const float GRAVITY;
    void capVelocity();
};
}

#endif /* MOVINGENTITY_H_ */
