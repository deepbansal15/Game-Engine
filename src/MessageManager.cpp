/*
 * MessageManager.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: nathan
 */

#include "MessageManager.h"

namespace TileEngine
{
void MessageManager::discharge(TileEngine::Entity* receiver,
		const TileEngine::Telegram &msg)
{
	if (!receiver->handleMessage(msg))
	{
		//message not handled
	}
}

void MessageManager::dispatchMsg(double delay, int sender, int receiver,
		int msg, void* AdditionalInfo = NULL)
{
	Entity* pReceiver = EntityMgr->getEntityFromID(receiver);

	if( pReceiver == NULL )
	{
		return;
	}

	Telegram telegram(0, sender, receiver, msg, AdditionalInfo);

	if(delay <= 0.0)
	{
		discharge(pReceiver, telegram);
	}
	else
	{
		double currentTime = SDL_GetTicks();
		telegram.dispatchTime = currentTime + delay;

		PriorityQ.insert(telegram);
	}
}

void MessageManager::dispatchDelayedMessages()
{
	//first get current time
	double currentTime = SDL_GetTicks();

	//now peek at the queue to see if any telegrams need dispatching.
	//remove all telegrams from the front of the queue that have gone
	//past their sell by date
	while (!PriorityQ.empty() && (PriorityQ.begin()->dispatchTime < currentTime)
			&& (PriorityQ.begin()->dispatchTime > 0))
	{
		//read the telegram from the front of the queue
		const Telegram& telegram = *PriorityQ.begin();

		//find the recipient
		Entity* pReceiver = EntityMgr->getEntityFromID(telegram.receiver);

		//send the telegram to the recipient
		discharge(pReceiver, telegram);

		//remove it from the queue
		PriorityQ.erase(PriorityQ.begin());
	}
}

}
