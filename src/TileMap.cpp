/*
 * TileMap.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#include "TileMap.h"

namespace TileEngine
{
const std::string TileMap::LAYERS_TAG = "[Layers]";
const std::string TileMap::COLLISION_TAG = "col";

TileMap::TileMap(std::string mapName)
{
	createMap(mapName);
}

TileMap::~TileMap()
{
	for (uint i = 0; i < layers.size(); i++)
	{
		delete layers[i];
	}
	layers.clear();
}

void TileMap::createMap(std::string filename)
{
	bool readingLayers = false;
	std::string absFileName = RESOURCE_DIR + MAP_DIR + filename;

	std::vector<std::string> tmpLayers;
	std::string line;

	CommandList clist = CommandList::processFile(absFileName);

	for (int i = 0; i < clist.size(); i++)
	{
		std::string keyword = clist[i][0];
		if (keyword == TileMap::LAYERS_TAG)
		{
			readingLayers = true;
		}
		else if (readingLayers)
		{
			std::vector<std::string> layer = clist[i];
			if( COLLISION_TAG == layer[0] )
            {
                colayer = new CollisionLayer(layer[1]);
	    	}
            else
            {
                tmpLayers.push_back(layer[0]);
            }
        }
	}

	for (uint i = 0; i < tmpLayers.size(); i++)
	{
		layers.push_back(new TileLayer(tmpLayers[i]));
	}
}

int TileMap::getWidth()
{
	int width = -1;

	for (uint i = 0; i < layers.size(); i++)
	{
		width = std::max(width, layers[i]->getWidth());
	}
	return width;
}

int TileMap::getHeight()
{
	int height = -1;

	for (uint i = 0; i < layers.size(); i++)
	{
		height = std::max(height, layers[i]->getHeight());
	}
	return height;
}

int TileMap::getMapWidthInPixels()
{
	return getWidth() * TILE_WIDTH;
}

int TileMap::getMapHeightInPixels()
{
	return getHeight() * TILE_HEIGHT;
}

void TileMap::draw(SDL_Surface* screen, Camera camera)
{
	Point min = convertPositionToCell(camera.getPosition());
	Point max = convertPositionToCell(
			Vector2(Window::screenWidth() + TILE_WIDTH + camera.getPosition().X,
					Window::screenHeight() + TILE_HEIGHT
							+ camera.getPosition().Y));
	for (uint i = 0; i < layers.size(); i++)
	{
		layers[i]->draw(screen, camera, min, max);
	}
}

}
