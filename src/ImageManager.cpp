/*
 * ImageManager.cpp
 *
 *  Created on: Jan 15, 2013
 *      Author: nathan
 */

#include "ImageManager.h"

namespace TileEngine
{


SDL_Surface* const ImageManager::acquireSurface(const std::string& fileName)
{
	std::string absFileName = RESOURCE_DIR + IMAGE_DIR + fileName;
	SurfaceIterator surfaceElement = surfaces.find(absFileName);

	// If we've already loaded this resource, simply increment the counter
	// in the tracker and return the surface
	//
	// Otherwise, load it and add it to the tracker with an initial count of 1
	if (surfaceElement != surfaces.end())
	{
		TrackerIterator trackerElement = tracker.find(absFileName);
		++trackerElement->second;
		return surfaceElement->second;
	}
	else
	{
		SDL_Surface* surface = loadImage(absFileName);
		if (surface != 0)
		{
			tracker.insert(std::make_pair(absFileName, 1));
			surfaces.insert(std::make_pair(absFileName, surface));
			return surface;
		}
		else
		{
			throw Exception("Failed to load file: " + absFileName);
		}
	}
}

void ImageManager::releaseSurface(const std::string& fileName)
{
	std::string absFileName = RESOURCE_DIR + IMAGE_DIR + fileName;
	// If the resource already exists, check its tracker count.
	// If it is currently 1, we are removing the last handle to it
	// so we need to free the resource and remove it from our map.
	//
	// Otherwise, just decrease the count in the tracker
	SurfaceIterator surfaceElement = surfaces.find(absFileName);

	if (surfaceElement != surfaces.end())
	{
		TrackerIterator trackerElement = tracker.find(absFileName);
		if (trackerElement->second == 1)
		{
			trackerElement->second = 0;
			SDL_FreeSurface(surfaceElement->second);
			surfaceElement->second = 0;
			surfaces.erase(surfaceElement);
			tracker.erase(trackerElement);
		}
		else
		{
			--trackerElement->second;
		}
	}
}

void ImageManager::releaseSurface(SDL_Surface* surface)
{
	// If the resource already exists, check its tracker count.
	// If it is currently 1, we are removing the last handle to it
	// so we need to free the resource and remove it from our map.
	//
	// Otherwise, just decrease the count in the tracker
	SurfaceIterator surfaceElement;

	std::string filename = "";

	for(surfaceElement = surfaces.begin(); surfaceElement != surfaces.end(); ++surfaceElement)
	{
		if(surfaceElement->second == surface)
		{
			filename = surfaceElement->first;
			break;
		}
	}

	if (surfaceElement != surfaces.end())
	{
		TrackerIterator trackerElement = tracker.find(filename);
		if (trackerElement->second == 1)
		{
			trackerElement->second = 0;
			SDL_FreeSurface(surfaceElement->second);
			surfaceElement->second = 0;
			surfaces.erase(surfaceElement);
			tracker.erase(trackerElement);
		}
		else
		{
			--trackerElement->second;
		}
	}
}

SDL_Surface* ImageManager::loadImage(std::string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	bool pngEnding = hasEnding(filename ,"png");
	if (loadedImage != NULL)
	{
		if(pngEnding)
		{
			optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		}
		else{
			optimizedImage = SDL_DisplayFormat(loadedImage);
		}
		SDL_FreeSurface(loadedImage);
	}

	if (!pngEnding && optimizedImage != NULL)
	{
		/// This will cause problems with pre transparent pictures.
		//Map the color key
		Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);

		//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
		SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
	}

	return optimizedImage;
}

void ImageManager::applySurface(int x, int y, SDL_Surface* source,
		SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, clip, destination, &offset);
}

Uint32 ImageManager::getPixel32(SDL_Surface* surface, int x, int y)
{
	//Convert the pixel to 32 bit
	Uint32 *pixels = (Uint32*) surface->pixels;

	//Get the requested pixel
	return pixels[(y * surface->w) + x];
}

void ImageManager::putPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *) surface->pixels;
	//Set the pixel
	pixels[(y * surface->w) + x] = pixel;
}
}
