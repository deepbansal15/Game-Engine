/*
 * CommandList.h
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#ifndef COMMANDLIST_H_
#define COMMANDLIST_H_

#include "Globals.h"
#include "Random.h"

namespace TileEngine
{

class CommandList
{
	typedef std::vector<std::string> Command;
	typedef Command::iterator CommandIter;
public:
	CommandList(){}
	virtual ~CommandList(){}

	Command operator[](int index);

	void addCommand(Command);
	void removeCommand(Command);
	Command getCommand(int index);
	bool contains(Command);
	int size(){ return commandList.size(); }
	void clear();

	static CommandList processFile(std::string filename);
private:
	std::vector<Command> commandList;
};
}

#endif /* COMMANDLIST_H_ */
