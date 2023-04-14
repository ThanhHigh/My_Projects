

#include "LevelPart.hpp"
#include "Camera.hpp"

LevelPart* LevelPart::s_Instance = nullptr;

LevelPart::LevelPart(int p_x, int p_y, GameMap* gamemap)
{
    //flag loadTiled
    bool success = true;

    //offset
    int x = p_x;
    int y = p_y;

    //load
    success = MapParser::GetInstance()->load();
    // GameMap* levelgamemap = nullptr;
    // levelgamemap = MapParser::GetInstance()->GetMap(id);
    levelgamemap = gamemap;
}

void LevelPart::setLevelMap(GameMap* gamemap)
{
    levelgamemap = gamemap;
}

void LevelPart::renderLevelPart() 
{
    levelgamemap->render(x, y);
}

void LevelPart::renderLevelPart(int p_x)
{
    x = p_x;
    levelgamemap->render(x, y);
}

void LevelPart::setLevelX(GameMap* gameMap)
{
    x = gameMap->getMapX() + LEVEL_WIDTH;
}

void  LevelPart::setLevelX(int p_x)
{
    x = p_x;
}