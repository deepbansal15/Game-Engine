/*
 * Telegram.h
 *
 *  Created on: Jan 31, 2013
 *      Author: nathan
 */

#ifndef TELEGRAM_H_
#define TELEGRAM_H_

#ifndef NULL
#define NULL 0
#endif

#include <cmath>
#include <iostream>

namespace TileEngine
{

struct Telegram
{
	int sender;
	int receiver;

	int msg;

	double dispatchTime;
	void* extraInfo;

	Telegram():dispatchTime(-1),
			sender(-1),
			receiver(-1),
			msg(-1),
			extraInfo(NULL)
	{}

	Telegram(double time,
			int sender,
			int receiver,
			int msg,
			void* info = NULL):dispatchTime(time),
					sender(sender),
					receiver(receiver),
					msg(msg),
					extraInfo(info)
	{}
};


//these telegrams will be stored in a priority queue. Therefore the >
//operator needs to be overloaded so that the PQ can sort the telegrams
//by time priority. Note how the times must be smaller than
//SmallestDelay apart before two Telegrams are considered unique.
const double SmallestDelay = 0.25;


inline bool operator==(const Telegram& t1, const Telegram& t2)
{
  return ( fabs(t1.dispatchTime-t2.dispatchTime) < SmallestDelay) &&
          (t1.sender == t2.sender)        &&
          (t1.receiver == t2.receiver)    &&
          (t1.msg == t2.msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
  if (t1 == t2)
  {
    return false;
  }

  else
  {
    return  (t1.dispatchTime < t2.dispatchTime);
  }
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
  os << "time: " << t.dispatchTime << "  sender: " << t.sender
     << "   receiver: " << t.receiver << "   msg: " << t.msg;

  return os;
}

//handy helper function for dereferencing the ExtraInfo field of the Telegram
//to the required type.
template <class T>
inline T dereferenceToType(void* p)
{
  return *(T*)(p);
}

}

#endif /* TELEGRAM_H_ */
