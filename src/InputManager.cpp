/*
 * InputManager.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#include "InputManager.h"
#include <iostream>

namespace TileEngine
{


InputManager::InputManager()
{
	updateFreq = 100;
	initMapKeys();
	timer.start();
}

InputManager::~InputManager()
{
	// TODO Auto-generated destructor stub
}

bool InputManager::keyPressed(SDLKey key)
{
	if (keyState[key] && !previousKeyState[key])
		return true;
	return false;
}

bool InputManager::keyHeld(SDLKey key)
{
	if (keyState[key] && previousKeyState[key])
		return true;
	return false;
}

bool InputManager::keyReleased(SDLKey key)
{
	if (!keyState[key] && previousKeyState[key])
		return true;
	return false;
}

void InputManager::update()
{
	if (timer.getTicks() > updateFreq)
	{
		previousKeyState = keyState;
		timer.start();
	}
}

void InputManager::initMapKeys()
{
	//Map the Alphabet
	keyState.insert(std::make_pair(SDLK_a, false));
	keyState.insert(std::make_pair(SDLK_b, false));
	keyState.insert(std::make_pair(SDLK_c, false));
	keyState.insert(std::make_pair(SDLK_d, false));
	keyState.insert(std::make_pair(SDLK_e, false));
	keyState.insert(std::make_pair(SDLK_f, false));
	keyState.insert(std::make_pair(SDLK_g, false));
	keyState.insert(std::make_pair(SDLK_h, false));
	keyState.insert(std::make_pair(SDLK_i, false));
	keyState.insert(std::make_pair(SDLK_j, false));
	keyState.insert(std::make_pair(SDLK_k, false));
	keyState.insert(std::make_pair(SDLK_l, false));
	keyState.insert(std::make_pair(SDLK_m, false));
	keyState.insert(std::make_pair(SDLK_n, false));
	keyState.insert(std::make_pair(SDLK_o, false));
	keyState.insert(std::make_pair(SDLK_p, false));
	keyState.insert(std::make_pair(SDLK_q, false));
	keyState.insert(std::make_pair(SDLK_r, false));
	keyState.insert(std::make_pair(SDLK_s, false));
	keyState.insert(std::make_pair(SDLK_t, false));
	keyState.insert(std::make_pair(SDLK_u, false));
	keyState.insert(std::make_pair(SDLK_v, false));
	keyState.insert(std::make_pair(SDLK_w, false));
	keyState.insert(std::make_pair(SDLK_x, false));
	keyState.insert(std::make_pair(SDLK_y, false));
	keyState.insert(std::make_pair(SDLK_z, false));

	//Map regular numbers
	keyState.insert(std::make_pair(SDLK_0, false));
	keyState.insert(std::make_pair(SDLK_1, false));
	keyState.insert(std::make_pair(SDLK_2, false));
	keyState.insert(std::make_pair(SDLK_3, false));
	keyState.insert(std::make_pair(SDLK_4, false));
	keyState.insert(std::make_pair(SDLK_5, false));
	keyState.insert(std::make_pair(SDLK_6, false));
	keyState.insert(std::make_pair(SDLK_7, false));
	keyState.insert(std::make_pair(SDLK_8, false));
	keyState.insert(std::make_pair(SDLK_9, false));

	//Map numpad keys
	keyState.insert(std::make_pair(SDLK_KP0, false));
	keyState.insert(std::make_pair(SDLK_KP1, false));
	keyState.insert(std::make_pair(SDLK_KP2, false));
	keyState.insert(std::make_pair(SDLK_KP3, false));
	keyState.insert(std::make_pair(SDLK_KP4, false));
	keyState.insert(std::make_pair(SDLK_KP5, false));
	keyState.insert(std::make_pair(SDLK_KP6, false));
	keyState.insert(std::make_pair(SDLK_KP7, false));
	keyState.insert(std::make_pair(SDLK_KP8, false));
	keyState.insert(std::make_pair(SDLK_KP9, false));

	keyState.insert(std::make_pair(SDLK_UP, false));
	keyState.insert(std::make_pair(SDLK_DOWN, false));
	keyState.insert(std::make_pair(SDLK_LEFT, false));
	keyState.insert(std::make_pair(SDLK_RIGHT, false));

	keyState.insert(std::make_pair(SDLK_BACKSPACE, false));
	keyState.insert(std::make_pair(SDLK_TAB, false));
	keyState.insert(std::make_pair(SDLK_CLEAR, false));
	keyState.insert(std::make_pair(SDLK_RETURN, false));
	keyState.insert(std::make_pair(SDLK_PAUSE, false));
	keyState.insert(std::make_pair(SDLK_ESCAPE, false));
	keyState.insert(std::make_pair(SDLK_SPACE, false));

	//Map ctrl, shift and alt
	keyState.insert(std::make_pair(SDLK_LSHIFT, false));
	keyState.insert(std::make_pair(SDLK_RSHIFT, false));
	keyState.insert(std::make_pair(SDLK_LCTRL, false));
	keyState.insert(std::make_pair(SDLK_RCTRL, false));
	keyState.insert(std::make_pair(SDLK_LALT, false));
	keyState.insert(std::make_pair(SDLK_RALT, false));

	previousKeyState = keyState;
}

void InputManager::processEvent(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
	{
		keyState[event.key.keysym.sym] = true;
		break;
	}
	case SDL_KEYUP:
	{
		keyState[event.key.keysym.sym] = false;
		break;
	}
	}
}
}
