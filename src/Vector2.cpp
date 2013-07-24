/*
 * Vector2.cpp
 *
 *  Created on: Jan 16, 2013
 *      Author: nathan
 */

#include "Vector2.h"

namespace TileEngine
{

Vector2::Vector2()
{
	X = 0;
	Y = 0;
}

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Vector2::~Vector2()
{
	// TODO Auto-generated destructor stub
}

void Vector2::operator=(float num)
{
    X = num;
    Y = num;
}
Vector2 Vector2::operator=(const Vector2& vect)
{
    X = vect.X;
    Y = vect.Y;

    return *this;
}

Vector2 Vector2::operator+(const Vector2& vect)
{
	return Vector2(X + vect.X, Y + vect.Y);
}

Vector2 Vector2::operator-(const Vector2& vect)
{
	return Vector2(X - vect.X, Y - vect.Y);
}

Vector2 Vector2::operator*(const Vector2& vect)
{
	return Vector2(X * vect.X, Y * vect.Y);
}

void Vector2::operator-=(const Vector2& vect)
{
	subtract(vect);
}

void Vector2::operator+=(const Vector2& vect)
{
	add(vect);
}

void Vector2::operator*=(const Vector2& vect)
{
	multiply(vect);
}

void Vector2::operator/=(const Vector2& vect)
{
	divide(vect);
}

void Vector2::operator*=(float num)
{
	multiply(num);
}

void Vector2::operator/=(float num)
{
	divide(num);
}


void Vector2::add(const Vector2 &vect)
{
	X += vect.X;
	Y += vect.Y;
}

void Vector2::subtract(const Vector2 &vect)
{
	X -= vect.X;
	Y -= vect.Y;
}

void Vector2::multiply(const Vector2 &vect)
{
	X *= vect.X;
	Y *= vect.Y;
}

void Vector2::divide(const Vector2 &vect)
{
	X = (vect.X == 0) ? X : X / vect.X;
	Y = (vect.Y == 0) ? Y : Y / vect.Y;
}

void Vector2::multiply(float value)
{
	X *= value;
	Y *= value;
}

void Vector2::divide(float value)
{
	if (value != 0)
	{
		X /= value;
		Y /= value;
	}
}

}
