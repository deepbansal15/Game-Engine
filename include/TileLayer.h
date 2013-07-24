/*
 * TileLayer.h
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#ifndef TILELAYER_H_
#define TILELAYER_H_

#include "ITileLayer.h"
#include "Globals.h"
#include "Camera.h"
#include "Point.h"
#include "ImageManager.h"
#include "ResourceManager.h"
#include "CommandList.h"

namespace TileEngine
{


class TileLayer : public ITileLayer
{
public:
	TileLayer(std::string filename);
	virtual ~TileLayer();

	void draw(SDL_Surface* screen, Camera c, Point min, Point max);

private:
    static const std::string IMAGE_DIR;
	static const std::string TEXTURE_TAG;

	void processFile(std::string fileName);
	std::vector<SDL_Surface*> textures;
};
}

#endif /* TILELAYER_H_ */
