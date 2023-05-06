
#include "MapParser.hpp"
#include "LevelPart.hpp"

//Initilize
MapParser* MapParser::s_Instance = nullptr;

// MapParser::MapParser()
// {
// }

// MapParser::~MapParser()
// {
// }

bool MapParser::load()
{
    bool success = true;
    if (!Parse("map1", "res/Map2.tmx")) success = false;
    if (!Parse("map2", "res/Map2B.tmx")) success = false;
    if (!Parse("map3", "res/Map2C.tmx")) success = false;
    if (!Parse("map4", "res/Map2D.tmx")) success = false;
    if (!Parse("map5", "res/Map2E.tmx")) success = false;
    if (!Parse("map_spawn", "res/Map2spawn.tmx")) success = false;

    if (success == false)
    {
        std::cout << "FAILED TO LOAD MAPS" << std::endl;
    }
    return success;
}


bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if (xml.Error()) //Error
    {
        std::cerr << "Failed to load: " << source << std::endl; //What cerr ?
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;

    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    //Parser Tiled sets
    tileSetList tilesets;
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {   
            tilesets.push_back(ParseTileset(e));
        }
    }

    //Parser Layers
    GameMap* gamemap = new GameMap();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }
    
    m_MapDict[id] = gamemap;

    return true;
}

TileSet MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    TileSet tileset;
    tileset.name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.firstID);

    xmlTileset->Attribute("tilecount", &tileset.tileCount);
    tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.colCount);
    tileset.rowCout = tileset.tileCount/tileset.colCount;
    xmlTileset->Attribute("tilewidth", &tileset.tileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.source = image->Attribute("source");

    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, tileSetList tilesets, int tilesize, int rowcount, int colcount)
{
    //Get data
    TiXmlElement* data;
    for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
        if (e->Value() == std::string("data"))
        {
            data = e;
            break;
        }

    //Parse Layer tile map
    std::string matrix(data->GetText());
    std::stringstream iss(matrix);
    std::string id;

    ///tilemap
    tileMap tilemap(rowcount, std::vector<int>(colcount, 0));

    for (int row = 0; row < rowcount; row++)
    {
        for (int col = 0; col < colcount; col++)
        {
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if (!iss.good()) //Error:
                break;
        }
    }

    // func return tileLayer
    //return (new TileLayer(tilesize, colcount, rowcount, tilemap, tilesets));
    TileLayer* re_TileLayer = new TileLayer(tilesize, colcount, rowcount, tilemap, tilesets);
    return re_TileLayer;
}

void MapParser::clean()
{
    //Clear our map
    std::map <std::string, GameMap*> ::iterator it;
    for (it = m_MapDict.begin(); it != m_MapDict.end(); it++)
    {
        it->second = nullptr;
    }

    m_MapDict.clear();
    //Debug 
        std::cout << "Clear Map in MapParaser !" << std::endl;
    //Debug
}
