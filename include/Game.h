/*
 * Game.h
 *
 *  Created on: Jan 14, 2013
 *      Author: nathan
 */

#ifndef GAME_H_
#define GAME_H_

#include "Globals.h"
#include "Timer.h"
#include "Window.h"
#include "World.h"
#include "InputManager.h"
#include <ctime>

namespace TileEngine
{


class Game
{
public:
	Game();

	bool init(char* title, int width, int height, int bp);
	void clean();

	void run();

	void handleEvents();
	void update();
	void draw();

	bool isRunning() const
	{
		return running;
	}

	virtual ~Game()
	{
	}

private:
	bool running;
	int FRAMES_PER_SECOND;
	World* world;
	Window* window;
};

}

#endif /* Game_H_ */
