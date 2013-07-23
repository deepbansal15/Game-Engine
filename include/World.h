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
#include "Timer.h"
#include "Message.h"
#include "InputManager.h"
#include "Window.h"
#include "MovingEntity.h"
#include "Player.h"
#include "EntityManager.h"

namespace TileEngine
{

class World
{
public:
	World();
	virtual ~World();

	bool init();
	void update();
	void handleEvents();
	void draw(SDL_Surface* screen);
	void clean();

private:
	void calculateFPS();

	int frameCount;
    int timerMsgDistance;
	Message* seconds;
	Message* fpsDisplay;
	Timer updateFPS;
	Timer timer;
	Camera camera;
    Player* player;
};
}

#endif /* WORLD_H_ */
