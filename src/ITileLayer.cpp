#include "ITileLayer.h"

namespace TileEngine
{

const std::string ITileLayer::LAYOUT_TAG = "[Layout]";
ITileLayer::ITileLayer()
{
    width = 0;
    height = 0;
    filename = "";
}

int ITileLayer::getWidth() const
{
    return width;
}

int ITileLayer::getHeight() const
{
    return height;
}

int ITileLayer::getTile(Point p) const
{
    return getTile(p.X, p.Y);
}

int ITileLayer::getTile(int x, int y) const
{
    if( x>= 0 && x < width && y >= 0 && y < height)
        return tiles[x][y];
    else
        return -1;
}

void ITileLayer::setTileIndex(int x, int y, int value)
{
    if( x >= 0 && x < width && y >= 0 && y < height)
        tiles[y][x] = value;
}


ITileLayer::~ITileLayer()
{

}
}
