/*
 * Random.h
 *
 *  Created on: Jan 18, 2013
 *      Author: nathan
 */

#ifndef RANDOM_H_
#define RANDOM_H_
#include <sstream>
#include <string>
#include <stdexcept>

namespace TileEngine
{

class Exception : public std::runtime_error
{
public:
	Exception(const std::string& msg) : std::runtime_error(msg.c_str()){}
};


std::string strConcatenateNum(const std::string &str, int num);
std::string numToStr(int num);
bool hasEnding(std::string const &fullString, std::string const &ending);

}
#endif /* RANDOM_H_ */
