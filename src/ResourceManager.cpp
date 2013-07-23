/*
 * ResourceManager.cpp
 *
 *  Created on: Jan 18, 2013
 *      Author: nathan
 */

#include "ResourceManager.h"
#include <iostream>

namespace TileEngine
{


TTF_Font* const ResourceManager::acquireFont(const std::string& fileName, int size)
{
	std::string absFileName = RESOURCE_DIR + FONT_DIR + fileName;
	std::string finalName = strConcatenateNum(absFileName, size);
	FontIterator fontElement = fonts.find(finalName);

	// If we've already loaded this resource, simply increment the counter
	// in the tracker and return the surface
	//
	// Otherwise, load it and add it to the tracker with an initial count of 1
	if (fontElement != fonts.end())
	{
		TrackerIterator trackerElement = tracker.find(finalName);

		++trackerElement->second;
		return fontElement->second;
	}
	else
	{
		TTF_Font* font = TTF_OpenFont(absFileName.c_str(), size);
		if (font != 0)
		{
			tracker.insert(std::make_pair(finalName, 1));
			fonts.insert(std::make_pair(finalName, font));
			return font;
		}
		else
		{
			throw Exception("Failed to load file: " + absFileName);
		}
	}
}

void ResourceManager::releaseFont(const std::string& fileName, int size)
{
	std::string absFileName = RESOURCE_DIR + FONT_DIR + fileName;
	std::string name = strConcatenateNum(absFileName, size);
	std::string fontSize = numToStr(size);

	std::string finalName = "";
	for(int i = 0; i < (name.length() - fontSize.length()); i++)
	{
		finalName += name[i];
	}

	// If the resource already exists, check its tracker count.
	// If it is currently 1, we are removing the last handle to it
	// so we need to free the resource and remove it from our map.
	//
	// Otherwise, just decrease the count in the tracker
	FontIterator fontElement = fonts.find(finalName);

	if (fontElement != fonts.end())
	{
		TrackerIterator trackerElement = tracker.find(finalName);

		if (trackerElement->second == 1)
		{
			trackerElement->second = 0;
			TTF_CloseFont(fontElement->second);
			fontElement->second = 0;
			fonts.erase(fontElement);
			tracker.erase(trackerElement);
		}
		else
		{
			--trackerElement->second;
		}
	}
}
}
