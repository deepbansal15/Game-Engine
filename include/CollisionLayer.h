/*
 * CollisionLayer.h
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#ifndef TILE_ENGINE_COLLISION_LAYER_H_
#define TILE_ENGINE_COLLISION_LAYER_H_

#include "ITileLayer.h"
#include "Globals.h"
#include "Camera.h"
#include "Point.h"
#include "ImageManager.h"
#include "ResourceManager.h"
#include "CommandList.h"

namespace TileEngine
{
class CollisionLayer : public ITileLayer
{
public:
	CollisionLayer(std::string filename);
	virtual ~CollisionLayer();

private:
	void processFile(std::string fileName);
};
}

#endif /* TILELAYER_H_ */
