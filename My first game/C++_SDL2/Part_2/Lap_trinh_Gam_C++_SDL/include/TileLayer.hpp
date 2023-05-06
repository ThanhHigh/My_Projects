#ifndef TileLayer_hpp
#define TileLayer_hpp

#include "Layer.hpp"


#include <vector>
#include <string>

struct TileSet
{
    int firstID, lastID;
    int rowCout, colCount;
    int tileCount, tileSize;

    std::string name, source;
};

using tileSetList = std::vector <TileSet>;
using tileMap = std::vector <std::vector <int> >;


class TileLayer : public Layer
{
    public:
        TileLayer(int tilesize, int colcount, int rowcount, tileMap tilemap, tileSetList tilesets);
        virtual void render();
        virtual void render(int p_x, int p_y);
        virtual void update();
        inline tileMap getTileMap() { return m_TileMap; }
        int getTileSize(){ return m_TileSize; }
        int getWidth() { return m_ColCount; }
        int getHeight() { return m_RowCount; }
    private:
        int m_TileSize;
        int m_RowCount, m_ColCount;
        tileMap m_TileMap;
        tileSetList m_TileSets;
};
#endif //TIleLayer_hpp