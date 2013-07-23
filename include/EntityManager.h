/*
 * EntityManager.h
 *
 *  Created on: Feb 1, 2013
 *      Author: nathan
 */

#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "Singleton.h"
#include "Entity.h"
#include <map>
#include <cassert>

namespace TileEngine
{

class EntityManager
{
	friend class Singleton<EntityManager>;
	typedef std::map<int, TileEngine::Entity*> EntityMap;

public:
	void registerEntity(TileEngine::Entity* entity);
	void removeEntity(TileEngine::Entity* entity);
	TileEngine::Entity* const getEntityFromID(int id) const;

	EntityMap::iterator getEntityIter()
	{
		return entityMap.begin();
	}
	EntityMap::iterator getEntityEnd()
	{
		return entityMap.end();
	}
	void reset(){ entityMap.clear(); }

private:
	EntityManager(){}
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);
	virtual ~EntityManager(){}

	EntityMap entityMap;

};

#define EntityMgr TileEngine::Singleton<EntityManager>()
} /* namespace TileEngine */
#endif /* ENTITYMANAGER_H_ */
