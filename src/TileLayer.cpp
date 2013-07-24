/*
 * TileLayer.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#include "TileLayer.h"

namespace TileEngine
{


const std::string TileLayer::IMAGE_DIR = "[ImageDir]";
const std::string TileLayer::TEXTURE_TAG = "[Textures]";

TileLayer::TileLayer(std::string fileName)
{
    processFile(fileName);
}

void TileLayer::processFile(std::string fileName)
{
    bool readingImageDir = false;
    bool readingTextures = false;
	bool readingLayout = false;

    std::string imageDir = TILE_IMG_DIR;
	std::vector<std::vector<int> > tempLayout;
	int lineCount = 0;

	std::string absFileName = RESOURCE_DIR + LAYER_DIR + fileName;

	filename = absFileName;
	CommandList clist = CommandList::processFile(absFileName);

	for (int i = 0; i < clist.size(); i++)
	{
		std::string keyword = clist[i][0];
        if (keyword == TileLayer::IMAGE_DIR)
        {
            readingImageDir = true;
            readingLayout = false;
            readingTextures = false;
        }
        else if (keyword == TileLayer::TEXTURE_TAG)
		{ 
            readingImageDir = false;
			readingLayout = false;
			readingTextures = true;
		}
		else if (keyword == TileLayer::LAYOUT_TAG)
		{
            readingImageDir = false;
			readingLayout = true;
			readingTextures = false;
		}
        else if( readingImageDir )
        {
            imageDir = keyword;
        }
		else if (readingTextures)
		{   
			std::string tileFilename = imageDir + keyword;
			SDL_Surface* surface = ImageManagerInst->acquireSurface(
					tileFilename);
			textures.push_back(surface);
		}
		else if (readingLayout)
		{
			std::vector<int> row;
			std::vector<std::string> cells = clist[i];

			for (uint i = 0; i < cells.size(); i++)
			{
				if (cells[i].length() > 0)
				{
					try
					{
						row.push_back(atoi(cells[i].c_str()));
					} catch (Exception& e)
					{
						std::cout << "Error formating line " << lineCount
								<< " in " << absFileName << std::endl;
					}
				}
			}
			tempLayout.push_back(row);
		}
		lineCount++;
	}
	width = tempLayout[0].size();
	height = tempLayout.size();

	tiles.resize(height);
	for (uint i = 0; i < tiles.size(); i++)
	{
		tiles[i].resize(width);
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			setTileIndex(x, y, tempLayout[y][x]);
		}
	}
}

void TileLayer::draw(SDL_Surface* screen, Camera camera, Point minPt,
		Point maxPt)
{
	minPt.X = (int) std::max(minPt.X, 0);
	minPt.Y = (int) std::max(minPt.Y, 0);

	maxPt.X = (int) std::min(maxPt.X, width);
	maxPt.Y = (int) std::min(maxPt.Y, height);

	SDL_Surface* texture;

	for (int x = minPt.X; x < maxPt.X; x++)
	{
		for (int y = minPt.Y; y < maxPt.Y; y++)
		{
			int textureIndex = tiles[y][x];

			if (textureIndex == -1)
				continue;

			try
			{
				texture = textures.at(textureIndex);
			} catch (std::out_of_range &e)
			{
				std::cout << "Error accessing texture index " << textureIndex
						<< " in filename " << filename << std::endl;
				exit(-1);
			}

			ImageManagerInst->applySurface(
					x * TILE_WIDTH - (int)camera.getPosition().X,
					y * TILE_HEIGHT - (int)camera.getPosition().Y,
					texture,
					screen);
		}
	}
}

TileLayer::~TileLayer()
{
	for (uint i = 0; i < textures.size(); i++)
	{
		ImageManagerInst->releaseSurface(textures[i]);
	}
	textures.clear();
}
}

