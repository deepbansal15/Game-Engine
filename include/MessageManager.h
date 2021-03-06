/*
 * MessageManager.h
 *
 *  Created on: Jan 31, 2013
 *      Author: nathan
 */

#ifndef MESSAGEMANAGER_H_
#define MESSAGEMANAGER_H_

#include <set>
#include <string>
#include "Telegram.h"
#include "Entity.h"
#include "Singleton.h"
#include "EntityManager.h"
#include "SDL/SDL.h"

namespace TileEngine
{


//to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0;
const int    NO_ADDITIONAL_INFO   = 0;
const int    SENDER_ID_IRRELEVANT = -1;


class MessageManager
{
	friend class Singleton<MessageManager>;
private:

  //a std::set is used as the container for the delayed messages
  //because of the benefit of automatic sorting and avoidance
  //of duplicates. Messages are sorted by their dispatch time.
  std::set<Telegram> PriorityQ;

  //this method is utilized by DispatchMsg or DispatchDelayedMessages.
  //This method calls the message handling member function of the receiving
  //entity, pReceiver, with the newly created telegram
  void discharge(TileEngine::Entity* pReceiver, const TileEngine::Telegram& msg);

  MessageManager(){}

  //copy ctor and assignment should be private
  MessageManager(const MessageManager&);
  MessageManager& operator=(const MessageManager&);

public:

  //send a message to another agent. Receiving agent is referenced by ID.
  void dispatchMsg(double      delay,
                   int         sender,
                   int         receiver,
                   int         msg,
                   void*       ExtraInfo);

  //send out any delayed messages. This method is called each time through
  //the main game loop.
  void dispatchDelayedMessages();
};

#define Dispatcher TileEngine::Singleton<MessageDispatcher>()

}

#endif /* MESSAGEMANAGER_H_ */
