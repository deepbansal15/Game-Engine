/*
 * State.h
 *
 *  Created on: Jan 25, 2013
 *      Author: nathan
 */

#ifndef STATE_H_
#define STATE_H_

namespace TileEngine
{

template<class entity>
class State
{
public:
	virtual void Enter(entity*)=0;
	virtual void Execute(entity*)=0;
	virtual void Exit(entity*)=0;
	virtual ~State(){}
};
}

#endif /* STATE_H_ */
