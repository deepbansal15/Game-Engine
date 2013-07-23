/*
 * Entity.h
 *
 *  Created on: Jan 25, 2013
 *      Author: nathan
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "SDL/SDL.h"
#include "ImageManager.h"
#include "Camera.h"
#include "Vector2.h"

namespace TileEngine
{

class Entity
{
public:
	Entity();
	virtual ~Entity();

	int getID(){ return ID; }

	bool checkCollision(Entity*);
	virtual void processCollision(const Entity*) = 0;

	virtual void update() = 0;
	virtual void draw(SDL_Surface* screen, Camera cam);
	virtual void handleEvents() = 0;

	void lockToScreen(int width, int height);

protected:
	static int next_available_ID;
	unsigned int ID;

	Vector2 position;

	SDL_Surface* image;
};
}

#endif /* ENTITY_H_ */
