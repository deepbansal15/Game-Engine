/*
 * Window.cpp
 *
 *  Created on: Jan 18, 2013
 *      Author: nathan
 */

#include "Window.h"
#include <iostream>

namespace TileEngine
{


int Window::SCREEN_WIDTH = 0;
int Window::SCREEN_HEIGHT = 0;
Window::Window()
{
	screen = NULL;
	windowed = false;
	windowOK = false;

	screenBPP = 0;
}

bool Window::init(char* title, int width, int height, int bpp)
{
	Window::SCREEN_WIDTH = width;
	Window::SCREEN_HEIGHT = height;
	screenBPP = bpp;

	screen = SDL_SetVideoMode(width, height, bpp,
			SDL_SWSURFACE | SDL_RESIZABLE);

	if (screen == NULL)
	{
		windowOK = false;
		return false;
	}
	windowOK = true;

	SDL_WM_SetCaption(title, NULL);
	windowed = true;

	return true;
}

void Window::setTitle(char* title)
{
	SDL_WM_SetCaption(title, NULL);
}

void Window::toggleFullscreen()
{
	if (windowed)
	{
		screen = SDL_SetVideoMode(Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT,
				screenBPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN);
		if (screen == NULL)
		{
			windowOK = false;
			return;
		}
		windowed = false;
	}
	else if (!windowed)
	{
		screen = SDL_SetVideoMode(Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT,
				screenBPP, SDL_SWSURFACE | SDL_RESIZABLE);
		if (screen == NULL)
		{
			windowOK = false;
			return;
		}
		windowed = true;
	}
}

void Window::handleEvent(SDL_Event event)
{
	if (!windowOK)
	{
		return;
	}

	if (event.type == SDL_VIDEORESIZE)
	{
		//Resize the screen
		Window::SCREEN_WIDTH = event.resize.w;
		Window::SCREEN_HEIGHT = event.resize.h;
		screen = SDL_SetVideoMode(Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT,
				screenBPP, SDL_SWSURFACE | SDL_RESIZABLE);

		//If there's an error
		if (screen == NULL)
		{
			windowOK = false;
			return;
		}
	}
	//If the window focus changed
	else if (event.type == SDL_ACTIVEEVENT)
	{
		//If the window was iconified or restored
		if (event.active.state & SDL_APPACTIVE)
		{
			//If the application is no longer active
			if (event.active.gain == 0)
			{
				//do stuff
			}
			else
			{
				//do stuff
			}
		}
	}
	//If something happened to the keyboard focus
	else if (event.active.state & SDL_APPINPUTFOCUS)
	{
		//If the application lost keyboard focus
		if (event.active.gain == 0)
		{
			//do stuff
		}
		else
		{
			//do stuff
		}
	}
	//If something happened to the mouse focus
	else if (event.active.state & SDL_APPMOUSEFOCUS)
	{
		//If the application lost mouse focus
		if (event.active.gain == 0)
		{
			//do stuff
		}
		else
		{
			//do stuff
		}
	}
	//If the window's screen has been altered
	else if (event.type == SDL_VIDEOEXPOSE)
	{
		if (SDL_Flip(screen) == -1)
		{
			//If there's an error
			windowOK = false;
			return;
		}
	}
}

Window::~Window()
{
	// TODO Auto-generated destructor stub
}
}
