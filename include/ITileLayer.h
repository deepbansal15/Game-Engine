#ifndef TILE_ENGINE_ITILE_LAYER
#define TILE_ENGINE_ITILE_LAYER

#include "SDL/SDL.h"
#include "Camera.h"
#include "Point.h"

#include <string>
#include <vector>

namespace TileEngine
{
class ITileLayer
{
    public:
        virtual ~ITileLayer();

        int getWidth() const;
        int getHeight()const ;

        int getTile(Point p) const;
        int getTile(int x, int y) const;
        void setTileIndex(int x, int y, int value);

    protected:
        static const std::string LAYOUT_TAG;
        
        ITileLayer();
        virtual void processFile(std::string fileName) = 0;
        
        std::string filename;
        int width;
        int height;
        std::vector<std::vector<int> > tiles;

};
};

#endif
