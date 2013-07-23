/*
 * CommandList.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#include "CommandList.h"

namespace TileEngine
{


std::vector<std::string> CommandList::operator[](int index)
{
	return getCommand(index);
}

void CommandList::addCommand(Command command)
{
	commandList.push_back(command);
}

void CommandList::removeCommand(Command command)
{
	int index = -1;
	for (unsigned int i = 0; i < commandList.size(); i++)
	{
		if (command == commandList[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		commandList.erase(commandList.begin() + index);
	}

}

std::vector<std::string> CommandList::getCommand(int index)
{
	if( index < 0 || index > size())
	{
		throw std::runtime_error("Accessing element outside the range of command list");
	}
	return commandList[index];
}

bool CommandList::contains(Command command)
{
	for (unsigned int i = 0; i < commandList.size(); i++)
	{
		if (command == commandList[i])
		{
			return true;
		}
	}
	return false;
}

void CommandList::clear()
{
	while (commandList.size() > 0)
	{
		commandList.pop_back();
	}
}

CommandList CommandList::processFile(std::string filename)
{
	std::ifstream myfile(filename.c_str());
	CommandList commands;

	if (myfile.is_open())
	{
		std::string comment = "//";
		std::string line;
		while (myfile.good())
		{
			getline(myfile, line);
			line = reassembleString(splitString(line, ' '));
			if (line.length() == 0)
				continue;
			if (line.substr(0, comment.size()) == comment)
				continue;

			commands.addCommand(splitString(line, ' '));
		}
		myfile.close();
	}
	else
	{
		std::cout << "Error reading file " << filename;
		exit(1);
	}
	return commands;
}
}
