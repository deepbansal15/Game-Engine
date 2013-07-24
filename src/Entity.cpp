/*
 * Entity.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: nathan
 */

#include "Entity.h"

namespace TileEngine
{

int Entity::next_available_ID = 0;
Entity::Entity()
{
	ID = next_available_ID;
	image = NULL;
	next_available_ID++;
}

Entity::~Entity()
{
}

void Entity::draw(SDL_Surface* screen, Camera cam)
{
	ImageManagerInst->applySurface(
			(int) (position.X - cam.getPosition().X),
			(int)(position.Y - cam.getPosition().Y),
			image,
			screen);
}

bool Entity::checkCollision(Entity* entity)
{
	int leftA = position.X;
	int rightA = position.X + image->w;
	int topA = position.Y;
	int bottomA = position.Y + image->h;

	int leftB = entity->position.X;
	int rightB = entity->position.X + entity->image->w;
	int topB = entity->position.Y;
	int bottomB = entity->position.Y + entity->image->h;

	if (bottomA <= topB)
	{
		return false;
	}
	if (topA >= bottomB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

void Entity::lockToScreen(int width, int height)
{
	if (position.X < 0)
		position.X = 0;
	if (position.Y < 0)
		position.Y = 0;
	if (position.X + image->w > width)
		position.X = width - image->w;
	if (position.Y + image->h > height)
		position.Y = height - image->h;
}
}
