/*
 * Game.cpp
 *
 *  Created on: Jan 14, 2013
 *      Author: nathan
 */

#include <Game.h>

namespace TileEngine
{


Game::Game()
{
	srand(time(NULL));
	running = false;
	FRAMES_PER_SECOND = 60;
	window = new Window();
	world = new World();
}

bool Game::init(char* title, int width, int height, int bp)
{
	running = true;
	if (!window->init(title, width, height, bp))
	{
		printf("ERROR -- Screen could not be initialized\n");
		return false;
	}

	if (!world->init("Map1.map"))
	{
		printf("ERROR -- World could not be initialized\n");
		return false;
	}

	return true;
}

void Game::clean()
{
	world->clean();
}

void Game::run()
{
	Timer timer;
	long beforeTime, afterTime, timeDiff;
	timer.start();

	beforeTime = timer.getTicks();
	while (running)
	{
		handleEvents();
		update();
		draw();

		afterTime = timer.getTicks();
		timeDiff = afterTime - beforeTime;

		if( timeDiff < (1000 / FRAMES_PER_SECOND))
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND ) - timeDiff);
		}

		beforeTime = timer.getTicks();
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		InputInst->processEvent(event);
		window->handleEvent(event);
		if (event.type == SDL_QUIT)
		{
			//Quit the program
			running = false;
		}
		if (InputInst->keyPressed(SDLK_ESCAPE))
		{
			running = false;
		}

		if (InputInst->keyPressed(SDLK_RETURN))
		{
			window->toggleFullscreen();
		}
	}
	world->handleEvents();
	InputInst->update();
}

void Game::update()
{
	world->update();
}

void Game::draw()
{
	if (window->error())
	{
		std::cout << "Error with window. Aborting draw." << std::endl;
		return;
	}
	//Clear screen
	SDL_FillRect(window->getScreen(), NULL,
			SDL_MapRGB(window->getScreen()->format, 0x00, 0x00, 0x00));
	world->draw(window->getScreen());
	SDL_Flip(window->getScreen());
}
}
