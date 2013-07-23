/*
 * ImageManager.h
 *
 *  Created on: Jan 15, 2013
 *      Author: nathan
 */

#ifndef IMAGEMANAGER_H_
#define IMAGEMANAGER_H_

#include "Globals.h"
#include "Singleton.h"
#include "Random.h"

namespace TileEngine
{

typedef std::map<std::string, SDL_Surface*>::iterator SurfaceIterator;
typedef std::map<std::string, int>::iterator TrackerIterator;

class ImageManager
{
	friend class Singleton<ImageManager> ;
public:
	SDL_Surface* const acquireSurface(const std::string& filename);
	void releaseSurface(const std::string& filename);
	void releaseSurface(SDL_Surface* surface);

	void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* dest,
			SDL_Rect* clip = NULL);

	Uint32 getPixel32(SDL_Surface* surface, int x, int y);
	void putPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);

private:

	std::map<std::string, int> tracker;
	std::map<std::string, SDL_Surface*> surfaces;

	ImageManager()
	{
	}
	ImageManager(const ImageManager&);
	ImageManager& operator=(const ImageManager&);
	SDL_Surface* loadImage(std::string filename);

	virtual ~ImageManager()
	{
	}
};

#define ImageManagerInst TileEngine::Singleton<ImageManager>()

}
#endif /* IMAGEMANAGER_H_ */
