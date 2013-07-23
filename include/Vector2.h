/*
 * Vector2.h
 *
 *  Created on: Jan 16, 2013
 *      Author: nathan
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <stdio.h>

namespace TileEngine
{

class Vector2
{
public:
	Vector2();
	Vector2( float x, float y );
    void operator=(float);
    Vector2 operator=(const Vector2& vect);
	Vector2 operator+(const Vector2& vect);
	Vector2 operator-(const Vector2& vect);
	Vector2 operator*(const Vector2& vect);

	void operator-=(const Vector2& vect);
	void operator+=(const Vector2& vect);
	void operator*=(const Vector2& vect);
	void operator/=(const Vector2& vect);

	void operator*=(float num);
	void operator/=(float num);

    Vector2 operator+(float num);
    Vector2 operator-(float num);
    Vector2 operator*(float num);
    Vector2 operator/(float num);

	virtual ~Vector2();

	void add( const Vector2 &vect );
	void subtract( const Vector2 &vect );
	void multiply( const Vector2 &vect );
	void divide( const Vector2 &vect );

	void multiply( float value );
	void divide( float value );

	float X, Y;
};

}
#endif /* VECTOR2_H_ */
