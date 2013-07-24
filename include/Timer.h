/*
 * Timer.h
 *
 *  Created on: Jan 17, 2013
 *      Author: nathan
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "SDL/SDL.h"

namespace TileEngine
{

class Timer
{
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	int getTicks();

	bool isStarted();
	bool isPaused();

private:
	int startTicks;
	int pausedTicks;

	bool paused;
	bool started;
};
}

#endif /* TIMER_H_ */
