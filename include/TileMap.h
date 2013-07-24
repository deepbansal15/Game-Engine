/*
 * TileMap.h
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "Globals.h"
#include "Camera.h"
#include "Vector2.h"
#include "Point.h"
#include "Window.h"
#include "TileLayer.h"
#include "CollisionLayer.h"
#include "CommandList.h"

namespace TileEngine
{

class TileMap
{
public:
	TileMap(std::string mapName);
	virtual ~TileMap();

	int getWidth();
	int getHeight();
	int getMapWidthInPixels();
	int getMapHeightInPixels();

    CollisionLayer* const cLayer() const{ return colayer; }
	void draw(SDL_Surface* screen, Camera cam);

private:

	void createMap(std::string);

	static const std::string LAYERS_TAG;
	static const std::string COLLISION_TAG;

	std::vector<TileEngine::TileLayer*> layers;
    CollisionLayer* colayer;
};
}

#endif /* TILEMAP_H_ */
