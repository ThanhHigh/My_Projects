//CollisionHandler.cpp
#include "CollisionHandler.hpp"
#include "Engine.hpp"
#include "Play.hpp"
//Debug
#include <iostream>


CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer*) Engine::GetInstance()->getMap()->m_GetMapLayers().back(); //back() is Collision
    m_CollisionTileMap =  m_CollisionLayer->getTileMap();
}

 void CollisionHandler::setCollisionMap(tileMap _tileMap, int _tilesize)
 {
    m_CollisionTileMap = _tileMap;
    m_MapTileSize = _tilesize;
    m_MapWidth = _tileMap.size();
    m_MapHeight = _tileMap[0].size();
 }

bool CollisionHandler::checkCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
        return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    //Add Debug
    m_CollisionLayer = (TileLayer*) Engine::GetInstance()->getMap()->m_GetMapLayers().back();; //back() is Collision
    m_CollisionTileMap =  m_CollisionLayer->getTileMap();
    //Add Debug


    //to fit with the data of the map
    if (m_MapTileSize != 16) m_MapTileSize = 16;
    if (m_MapWidth != 84) m_MapWidth = 84;
    if (m_MapHeight != 48) m_MapHeight = 48;

    int tileSize = m_MapTileSize;
    int rowCount = m_MapHeight;
    int colCount = m_MapWidth;

    //take the correct tile for loop under
    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;
    int top_tile = a.y / tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;

    
            //Add for infinity map
            if (left_tile >= colCount) left_tile = left_tile % colCount;
            if (right_tile >= colCount) right_tile  = right_tile % colCount;
            if (top_tile >= colCount) top_tile = top_tile % colCount;
            if (bottom_tile >= colCount) bottom_tile = bottom_tile % colCount;

            if (left_tile >= colCount) left_tile = colCount - 1;
            if (right_tile >= colCount) right_tile = colCount - 1;

    if (left_tile < 0) left_tile = 0; //Debug
    if (top_tile < 0) top_tile = 0; //Debug
    if (bottom_tile >= rowCount) bottom_tile = rowCount - 1;//Debug if (bottom_tile > rowCount) bottom_tile = rowCount - 1;

    for (int i = top_tile; i <= bottom_tile; i++)
    {
        for (int j = left_tile; j <= right_tile; j++)
        {

            if (m_CollisionTileMap[i][j] > 0)  
            { 
                return true;
            }
        }
    }

    //What if left_tile > right_tile
    if (left_tile > right_tile)
    {
        if (m_CollisionTileMap[top_tile][left_tile] > 0)  
            { 
                return true; 
            }
        if (m_CollisionTileMap[top_tile][right_tile] > 0)  
            { 
                return true; 
            }
        if (m_CollisionTileMap[bottom_tile][left_tile] > 0)  
            { 
                return true; 
            }
        if (m_CollisionTileMap[bottom_tile][right_tile] > 0) 
            { 
                return true; 
            }
    }

    return false; 
}

