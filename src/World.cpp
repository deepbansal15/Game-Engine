/*
 * World.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#include "World.h"

namespace TileEngine
{

World::World()
{
	frameCount = 0;
	seconds = NULL;
	fpsDisplay = NULL;
	map = NULL;
	camera.setSpeed(6);
}

World::~World()
{
	clean();
}

bool World::init(std::string mapName)
{
	map = new TileMap(mapName);
    EntityMgr->registerEntity(new MovingEntity("green_ball.png", 0, 0));
	seconds = new Message(" ", "lazy.ttf", 16);
	seconds->setX(Window::screenWidth() - seconds->getImage()->w);
	fpsDisplay = new Message("", "lazy.ttf", 16);

	//SoundMgr->playSound("beat.wav");
    //SoundMgr->playMusic("Attack.mp3");
	updateFPS.start();
	timer.start();
	calculateFPS();

	return true;
}

void World::update()
{
	seconds->setX(Window::screenWidth() - seconds->getImage()->w);

	frameCount++;

	std::stringstream time;
	double ticks = round(timer.getTicks() / 100) / 10;
	time << "Timer: " << ticks;
	seconds->setMessage(time.str());
	seconds->update();

	if (updateFPS.getTicks() > 1000)
	{
		calculateFPS();
	}

	int mapWidth = map->getMapWidthInPixels();
	int mapHeight = map->getMapHeightInPixels();

	std::map<int, TileEngine::Entity* >::iterator it;
	for( it = EntityMgr->getEntityIter(); it != EntityMgr->getEntityEnd(); ++it)
	{
		it->second->update();
		std::map<int, TileEngine::Entity* >::iterator secondIt;
		for( ++(secondIt = it); secondIt != EntityMgr->getEntityEnd(); ++secondIt)

		{
			if (it->second->checkCollision(secondIt->second))
			{
				it->second->processCollision(secondIt->second);
			}
		}
        it->second->processCollision(map->cLayer());
		it->second->lockToScreen(mapWidth, mapHeight);
	}

	//Loop through list checking for dead objects
}

void World::handleEvents()
{
	Vector2 motion;

	if (InputInst->keyHeld(SDLK_UP))
	{
		motion.Y -= 1;
	}
	if (InputInst->keyHeld(SDLK_LEFT))
	{
		motion.X -= 1;
	}
	if (InputInst->keyHeld(SDLK_DOWN))
	{
		motion.Y += 1;
	}
	if (InputInst->keyHeld(SDLK_RIGHT))
	{
		motion.X += 1;
	}

	motion *= camera.getSpeed();
	camera.getPosition() += motion;

	int width = map->getMapWidthInPixels() - Window::screenWidth();
	int height = map->getMapHeightInPixels() - Window::screenHeight();
	camera.lockCamera(width, height);

	std::map<int, TileEngine::Entity* >::iterator it;
	for( it = EntityMgr->getEntityIter(); it != EntityMgr->getEntityEnd(); ++it)
	{
		it->second->handleEvents();
	}
}

void World::draw(SDL_Surface* screen)
{
	map->draw(screen, camera);

	std::map<int, TileEngine::Entity* >::iterator it;
	for( it = EntityMgr->getEntityIter(); it != EntityMgr->getEntityEnd(); ++it)
	{
		it->second->draw(screen, camera);
	}
	ImageManagerInst->applySurface(seconds->X(), seconds->Y(), seconds->getImage(),
			screen);
	ImageManagerInst->applySurface(fpsDisplay->X(), fpsDisplay->Y(),
			fpsDisplay->getImage(), screen);

}

void World::calculateFPS()
{
	std::stringstream caption;

	caption << "FPS - " << frameCount / (timer.getTicks() / 1000.f);
	fpsDisplay->setMessage(caption.str());
	updateFPS.start();
}

void World::clean()
{
	if (seconds != NULL)
	{
		delete seconds;
	}
	if (fpsDisplay != NULL)
	{
		delete fpsDisplay;
	}
	if (map != NULL)
	{
		delete map;
	}
}

}
