/*
 * World.h
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "Camera.h"
#include "Vector2.h"
#include "Globals.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "TileMap.h"
#include "Timer.h"
#include "Message.h"
#include "InputManager.h"
#include "Window.h"
#include "MovingEntity.h"
#include "EntityManager.h"

namespace TileEngine
{

class World
{
public:
	World();
	virtual ~World();

	bool init(std::string mapName);
	void update();
	void handleEvents();
	void draw(SDL_Surface* screen);
	void clean();

private:
	void calculateFPS();

	int frameCount;
	Message* seconds;
	Message* fpsDisplay;
	Timer updateFPS;
	Timer timer;
	Camera camera;
	TileMap*  map;
};
}

#endif /* WORLD_H_ */
