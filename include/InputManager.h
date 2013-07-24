/*
 * InputManager.h
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include "SDL/SDL.h"
#include "Singleton.h"
#include "Timer.h"
#include <map>

namespace TileEngine
{

class InputManager
{
	friend class Singleton<InputManager>;
public:
	void processEvent(const SDL_Event& event);

	bool keyPressed(SDLKey key);
	bool keyHeld(SDLKey key);
	bool keyReleased(SDLKey key);

	void update();

private:
	InputManager();
	virtual ~InputManager();
	void initMapKeys();

	std::map<SDLKey, bool> keyState;
	std::map<SDLKey, bool> previousKeyState;

	Timer timer;
	int updateFreq;

};
}

#define InputInst TileEngine::Singleton<InputManager>()
#endif /* INPUTMANAGER_H_ */
