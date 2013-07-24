/*
 * Globals.h
 *
 *  Created on: Jan 18, 2013
 *      Author: nathan
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#include <stdexcept>

#include <vector>
#include <list>
#include <map>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include "Point.h"
#include "Vector2.h"

namespace TileEngine
{

const std::string RESOURCE_DIR = "Resources/";
const std::string FONT_DIR = "Fonts/";
const std::string AUDIO_DIR = "Audio/";

//Images
const std::string IMAGE_DIR = "Images/";
const std::string TILE_IMG_DIR = "Tiles/";

//Tilelayer and Tilemap directories
const std::string MAP_DIR = "Maps/";
const std::string LAYER_DIR = "Layers/";

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

#define uint unsigned int

inline std::vector<std::string> splitString(const std::string& string, char delim)
{
	std::vector<std::string> tokens;
	std::stringstream ss(string);
	std::string temp;

	while (getline(ss, temp, delim))
	{
		if (temp != "")
			tokens.push_back(temp);
	}
	return tokens;
}

inline std::string reassembleString(std::vector<std::string> list)
{
	std::string str;
	for( uint i = 0; i < list.size(); i++)
	{
		str.append(list[i]);
		if(i != list.size() - 1)
			str.append(" ");
	}
	return str;
}

inline Point convertPositionToCell(Vector2 position)
{
    return Point((int)(position.X / (float) TILE_WIDTH),
            (int)(position.Y / (float) TILE_HEIGHT));
}


}

#endif /* GLOBALS_H_ */
