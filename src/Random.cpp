/*
 * Random.cpp
 *
 *  Created on: Jan 18, 2013
 *      Author: nathan
 */

#include "Random.h"

namespace TileEngine
{


std::string strConcatenateNum(const std::string &str, int num)
{
	std::stringstream ss;
	ss << str << num;
	return ss.str();
}

std::string numToStr(int num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}

bool hasEnding (std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
}
