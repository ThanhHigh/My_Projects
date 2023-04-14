//CollisionHandler.cpp
#include "CollisionHandler.hpp"
#include "Engine.hpp"
//Debug
#include <iostream>

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer*) Engine::GetInstance()->getMap()->m_GetMapLayers().back(); //back() is Collision
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
    //to fit with the data of the mapj
    int tileSize = 16;
    int rowCount = 48;
    int colCount = 84;

    //take the correct tile for loop under
    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;
    int top_tile = a.y / tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;

    if (left_tile < 0) left_tile = 0; //Debug
    // if (right_tile > colCount) right_tile = colCount - 1; //Debug if (right_tile > colCount) right_tile = colCount - 1; //Map vo tan thi khong can cai nay
    if (top_tile < 0) top_tile = 0; //Debug
    if (bottom_tile > rowCount) bottom_tile = rowCount - 1;//Debug if (bottom_tile > rowCount) bottom_tile = rowCount - 1;


    //Check to no where in map have collision( where tile value more than 0)
    for (int i = top_tile; i <= bottom_tile; i++)
    {
        for (int j = left_tile; j <= right_tile; j++)
        {
            if (m_CollisionTileMap[i][j] > 0) { //Debug: defalut is  if (m_CollisionTileMap[i][j] > 0) {

                std::cout << "Oh Im Stuck " << i << " " << j << " " <<  m_CollisionTileMap[i][j] << std::endl;
                return false; //Debug return true;
            }
        }
    }

    return false; //Debug: Origin return false;
}

