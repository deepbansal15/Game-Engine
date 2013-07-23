/*
 * Camera.h
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector2.h"

namespace TileEngine
{

class Camera
{
public:
	Camera(): speed(4){}
	virtual ~Camera(){}

	static Vector2 zeroVector(){ return Vector2(); }

	Vector2& getPosition()
	{
		return position;
	}
        void setPosition(Vector2 position)
	{
		this->position = position;
	}
	float getSpeed()
	{
		return speed;
	}
	void setSpeed(float speed)
	{
		this->speed = speed;
	}
	void lockCamera(int width, int height)
	{
		if (position.X < 0)
			position.X = 0;
		if (position.Y < 0)
			position.Y = 0;
		if (position.X > width)
			position.X = width;
		if (position.Y > height)
			position.Y = height;
	}

private:
	float speed;
	Vector2 position;
};
}

#endif /* CAMERA_H_ */
