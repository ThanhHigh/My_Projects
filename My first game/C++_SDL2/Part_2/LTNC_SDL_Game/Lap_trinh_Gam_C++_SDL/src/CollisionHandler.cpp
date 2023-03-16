//CollisionHandler.cpp
#include "CollisionHandler.hpp"
#include "Engine.hpp"


CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer*) Engine::GetInstance()->getMap()->m_GetMapLayers().back();
    m_CollisionTileMap =  m_CollisionLayer->getTileMap();
}

bool CollisionHandler::checkCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
        return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    //to fit with the data of the map
    int tileSize = 32;
    int rowCount = 20;
    int colCount = 60;

    //take the correct tile for loop under
    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;
    int top_tile = a.y/tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;

    if (left_tile < 0) left_tile = 0;
    if (right_tile > colCount) right_tile = colCount;
    if (top_tile < 0) top_tile = 0;
    if (bottom_tile > rowCount) bottom_tile = rowCount;


    //Check to no where in map have collision( where tile value more than 0)
    for (int i = left_tile; i <= right_tile; i++)
    {
        for (int j = top_tile; j <= bottom_tile; j++)
        {
            if (m_CollisionTileMap[i][j] > 0)
                return true;
        }
    }

    return false;
}

