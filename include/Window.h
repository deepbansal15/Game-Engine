/*
 * Window.h
 *
 *  Created on: Jan 18, 2013
 *      Author: nathan
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL/SDL.h"

namespace TileEngine
{


class Window {
public:
	Window();
	virtual ~Window();

	bool init(char* title, int width, int height, int bpp);

	SDL_Surface* getScreen(){ return screen; }

	void setTitle(char* title);

	void handleEvent(SDL_Event event);
	void toggleFullscreen();
	bool error() { return !windowOK; }

	static int screenWidth(){ return Window::SCREEN_WIDTH;}
	static int screenHeight(){ return Window::SCREEN_HEIGHT;}
private:
	SDL_Surface* screen;

	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	int screenBPP;

	bool windowed;
	bool windowOK;
};
}

#endif /* WINDOW_H_ */
