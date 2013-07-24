/*
 * Point.h
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#ifndef POINT_H_
#define POINT_H_

namespace TileEngine
{

class Point
{
public:
	Point();
	Point(int x, int y);
	Point( const Point& );
	Point& operator=( const Point& );
	virtual ~Point();

	int X;
	int Y;
};

}

#endif /* POINT_H_ */
