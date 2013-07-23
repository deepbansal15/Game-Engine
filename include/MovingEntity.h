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
#include <string>
#include <cmath>
namespace TileEngine
{
class MovingEntity: public Entity
{
public:
	MovingEntity(std::string filename, int x, int y, float maxSpeed = 4);
	virtual ~MovingEntity();

	virtual void update();
	virtual void handleEvents();
	virtual void processCollision(const Entity* entity);

protected:
	Vector2 velocity;
    Vector2 acceleration;

    float maxSpeed;

private:
    void capVelocity();
};
}

#endif /* MOVINGENTITY_H_ */
