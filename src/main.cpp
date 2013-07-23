//============================================================================
// Name        : Simulation.cpp
// Author      : Nathan Rude
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "Game.h"

using namespace std;
using namespace TileEngine;

bool initSDL();
void quitSDL();

int main(int argc, char* args[])
{
	if(! initSDL())
	{
		printf("Error -- could not initialize SDL");
		return 1;
	}

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_BPP = 32;

	Game game;

	if( !game.init("Cynfawr",
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SCREEN_BPP))
	{
		printf("Error -- could not initialize the simulation");
		return 1;
	}
	game.run();
	game.clean();

	quitSDL();
	return 0;
}

bool initSDL()
{
	//Start SDL
	if( SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	if( TTF_Init() == -1 )
	{
		return false;
	}

	return true;
}

void quitSDL()
{
	//Quit SDL
	TTF_Quit();
	SDL_Quit();
}
