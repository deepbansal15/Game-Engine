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
    timerMsgDistance = 0;
	seconds = NULL;
	fpsDisplay = NULL;
	player = NULL;
    camera.setSpeed(6);
}

World::~World()
{
	clean();
}

bool World::init()
{
     
    player = new Player("green_ball.png", Window::screenWidth()/2 - 10, Window::screenHeight() - 40);
    EntityMgr->registerEntity(player);

	seconds = new Message(" ", "lazy.ttf", 16);
	seconds->setX(Window::screenWidth() - seconds->getImage()->w);
	fpsDisplay = new Message("", "lazy.ttf", 16);

//	SoundMgr->playSound("beat.wav");
    SoundMgr->playMusic("Attack.ogg");
	updateFPS.start();
	timer.start();
	calculateFPS();

	return true;
}

void World::update()
{
    //Keep the timer from fluctuating
    int timerMsgWidth =  seconds->getImage()->w;
    timerMsgDistance = (timerMsgDistance > timerMsgWidth) ? timerMsgDistance: timerMsgWidth;
    seconds->setX(Window::screenWidth() - timerMsgDistance);
	
    // Calculate Timer
	std::stringstream time;
	double ticks = round(timer.getTicks() / 100) / 10;
	time << "Timer: " << ticks;
	seconds->setMessage(time.str());
	seconds->update();

    //Framerate Shenanigans
    frameCount++;
	if (updateFPS.getTicks() > 1000)
	{
		calculateFPS();
	}


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
	}
    
    player->lockToScreen(Window::screenWidth(), Window::screenHeight());
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
//	camera.getPosition() += motion;

	std::map<int, TileEngine::Entity* >::iterator it;
	for( it = EntityMgr->getEntityIter(); it != EntityMgr->getEntityEnd(); ++it)
	{
		it->second->handleEvents();
	}
}

void World::draw(SDL_Surface* screen)
{
	std::map<int, TileEngine::Entity* >::iterator it;
	for( it = EntityMgr->getEntityIter(); it != EntityMgr->getEntityEnd(); ++it)
	{
		it->second->draw(screen, camera);
	}
	ImageManagerInst->applySurface(
            seconds->X(),
            seconds->Y(),
            seconds->getImage(),
			screen);

	ImageManagerInst->applySurface(
            fpsDisplay->X(),
            fpsDisplay->Y(),
			fpsDisplay->getImage(),
            screen);

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
    if (NULL != player)
    {
        delete player;
    }
}
}
