/*
 * Singleton.h
 *
 *  Created on: Jan 15, 2013
 *      Author: nathan
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace TileEngine
{


template <typename T>
class Singleton
{
public:
	static T& instance()
	{
		static T instance;
		return instance;
	}

	T* operator->() const { return &instance(); }
};
}

#endif /* SINGLETON_H_ */
