/*
 * EntityManager.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: nathan
 */

#include "EntityManager.h"
#include <iostream>

namespace TileEngine
{

void EntityManager::registerEntity(TileEngine::Entity* entity)
{
	if(entity == NULL)
	{
		return;
	}
	entityMap.insert(std::make_pair(entity->getID(), entity));
}

void EntityManager::removeEntity(TileEngine::Entity* entity)
{
	entityMap.erase(entityMap.find(entity->getID()));
}

TileEngine::Entity* const EntityManager::getEntityFromID(int id) const
{
	EntityMap::const_iterator it = entityMap.find(id);
	return (it != entityMap.end()) ? it->second : NULL;
}

} /* namespace TileEngine */
