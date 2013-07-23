/*
 * StateMachine.h
 *
 *  Created on: Jan 25, 2013
 *      Author: nathan
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include <cassert>
#include "State.h"

namespace TileEngine
{


template<class entity>
class StateMachine
{
private:
//a pointer to the agent that owns this instance
	entity* m_pOwner;
	State<entity>* m_pCurrentState;
//a record of the last state the agent was in
	State<entity>* m_pPreviousState;
//this state logic is called every time the FSM is updated
	State<entity>* m_pGlobalState;
public:
	StateMachine(entity* owner) :
			m_pOwner(owner),
			m_pCurrentState(0),
			m_pPreviousState(0),
			m_pGlobalState(0){}

	//use these methods to initialize the FSM
	void setCurrentState(State<entity>* s)
	{
		m_pCurrentState = s;
	}
	void setGlobalState(State<entity>* s)
	{
		m_pGlobalState = s;
	}
	void setPreviousState(State<entity>* s)
	{
		m_pPreviousState = s;
	}
	//call this to update the FSM
	void update() const
	{
		//if a global state exists, call its execute method
		if (m_pGlobalState)
			m_pGlobalState->Execute(m_pOwner);
		//same for the current state
		if (m_pCurrentState)
			m_pCurrentState->Execute(m_pOwner);
	}
	//change to a new state
	void changeState(State<entity>* pNewState)
	{
		assert(
				pNewState
						&& "<StateMachine::ChangeState>: trying to change to a null state");
		//keep a record of the previous state
		m_pPreviousState = m_pCurrentState;
		//call the exit method of the existing state
		m_pCurrentState->Exit(m_pOwner);
		//change state to the new state
		m_pCurrentState = pNewState;
		//call the entry method of the new state
		m_pCurrentState->Enter(m_pOwner);
	}
	//change state back to the previous state
	void revertToPreviousState()
	{
		changeState(m_pPreviousState);
	}
	//accessors
	State<entity>* currentState() const
	{
		return m_pCurrentState;
	}
	State<entity>* globalState() const
	{
		return m_pGlobalState;
	}
	State<entity>* previousState() const
	{
		return m_pPreviousState;
	}
	//returns true if the current state’s type is equal to the type of the
	//class passed as a parameter.
	bool isInState(const State<entity>& st) const;
};
}

#endif /* STATEMACHINE_H_ */
