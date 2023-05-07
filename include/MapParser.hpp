#ifndef MapParser_hpp
#define MapParser_hpp

//C++ headers
#include <map> 
/*
    <map> to save the maps. You can create more than one map
*/

#include <string>
//Other headers
#include "GameMap.hpp"
#include "TileLayer.hpp"
//XML include
#include "tinyxml.h"

class MapParser
{

    public:
        inline static MapParser* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new MapParser();
        }
        inline GameMap* GetMap(std::string id)
        {
            return m_MapDict[id];
        }

        bool load();
        void clean();

    private:
        bool Parse(std::string id, std::string source);
        TileSet ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, tileSetList tilesets, int tilesize, int rowcount, int colcount);

    private:
        MapParser(){}
        static MapParser* s_Instance;
        std::map <std::string, GameMap*> m_MapDict;
        friend class Engine;
        friend class LevelPart;
        friend class TileLayer;
};


#endif //MapParser_hpp