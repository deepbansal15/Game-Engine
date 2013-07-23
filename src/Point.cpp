/*
 * Point.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#include "Point.h"

namespace TileEngine
{

Point::Point()
{
	X = 0;
	Y = 0;
}
Point::Point(int x, int y)
{
	X = x;
	Y = y;
}
Point::Point(const Point& point)
{
	X = point.X;
	Y = point.Y;
}
Point& Point::operator=(const Point& point)
{
	X = point.X;
	Y = point.Y;

	return *this;
}

Point::~Point()
{
	// TODO Auto-generated destructor stub
}

}
