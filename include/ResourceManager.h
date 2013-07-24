/*
 * ResourceManager.h
 *
 *  Created on: Jan 18, 2013
 *      Author: nathan
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "Globals.h"
#include "ImageManager.h"
#include "Random.h"

namespace TileEngine
{


struct FontContainer
{
	TTF_Font* font;
	uint count;
};

typedef std::map<std::string, int>::iterator TrackerIterator;
typedef std::map<std::string, TTF_Font*>::iterator FontIterator;

class ResourceManager
{
	friend class Singleton<ResourceManager>;
public:
	TTF_Font* const acquireFont(const std::string& filename, int size);
	void releaseFont(const std::string& filename, int size);

private:
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, int> tracker;

	ResourceManager(){}
	ResourceManager(const ResourceManager&);
	ResourceManager& operator=(const ResourceManager&);
	virtual ~ResourceManager(){}
};

#define ResourceMgr TileEngine::Singleton<ResourceManager>()

}
#endif /* RESOURCEMANAGER_H_ */
