/*
 * CollisionLayer.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: nathan
 */

#include "CollisionLayer.h"

namespace TileEngine
{
    CollisionLayer::CollisionLayer(std::string filename)
    {
        processFile(filename);
    }

void CollisionLayer::processFile(std::string fileName)
{
	bool readingLayout = false;

	std::vector<std::vector<int> > tempLayout;
	int lineCount = 0;

	std::string absFileName = RESOURCE_DIR + LAYER_DIR + fileName;

	filename = absFileName;
	CommandList clist = CommandList::processFile(absFileName);

	for (int i = 0; i < clist.size(); i++)
	{
		std::string keyword = clist[i][0];
		if (keyword == CollisionLayer::LAYOUT_TAG)
		{
			readingLayout = true;
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

CollisionLayer::~CollisionLayer()
{
}
}
