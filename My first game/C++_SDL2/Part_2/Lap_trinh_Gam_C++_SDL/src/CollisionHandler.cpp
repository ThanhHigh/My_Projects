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
    //Add Debug
    m_CollisionLayer = (TileLayer*) Engine::GetInstance()->getMap()->m_GetMapLayers().back(); //back() is Collision
    m_CollisionTileMap =  m_CollisionLayer->getTileMap();
    //Add Debug


    //to fit with the data of the mapj
    int tileSize = 16;
    int rowCount = 48;
    int colCount = 84;

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
    // if (left_tile >= colCount) left_tile = colCount - 1;
    // if (right_tile >= colCount) right_tile = colCount - 1; //Debug if (right_tile > colCount) right_tile = colCount - 1; 
    //Debug
    if (left_tile > right_tile) std::cout << "Failed" << std::endl;
    //Debug


    //Check to no where in map have collision( where tile value more than 0)
    for (int i = top_tile; i <= bottom_tile; i++)
    {
        for (int j = left_tile; j <= right_tile; j++)
        {
            //Debug
            // std::cout << i << " " << j << " " << m_CollisionTileMap[i][j] << std::endl;
            //Debug

            if (m_CollisionTileMap[i][j] > 0)  //Debug: defalut is  if (m_CollisionTileMap[i][j] > 0) {
            { 
                // std::cout << "Oh Im Stuck " << i << " " << j << " " <<  m_CollisionTileMap[i][j] << std::endl;
                return true; //Debug return true;
            }
        }
    }

    //What if left_tile > right_tile
    if (left_tile > right_tile)
    {
        if (m_CollisionTileMap[top_tile][left_tile] > 0)  //Debug: defalut is  if (m_CollisionTileMap[i][j] > 0) {
            { 
                // std::cout << "Oh Im Stuck " << i << " " << j << " " <<  m_CollisionTileMap[i][j] << std::endl;
                return true; //Debug return true;
            }
        if (m_CollisionTileMap[top_tile][right_tile] > 0)  //Debug: defalut is  if (m_CollisionTileMap[i][j] > 0) {
            { 
                // std::cout << "Oh Im Stuck " << i << " " << j << " " <<  m_CollisionTileMap[i][j] << std::endl;
                return true; //Debug return true;
            }
        if (m_CollisionTileMap[bottom_tile][left_tile] > 0)  //Debug: defalut is  if (m_CollisionTileMap[i][j] > 0) {
            { 
                // std::cout << "Oh Im Stuck " << i << " " << j << " " <<  m_CollisionTileMap[i][j] << std::endl;
                return true; //Debug return true;
            }
        if (m_CollisionTileMap[bottom_tile][right_tile] > 0)  //Debug: defalut is  if (m_CollisionTileMap[i][j] > 0) {
            { 
                // std::cout << "Oh Im Stuck " << i << " " << j << " " <<  m_CollisionTileMap[i][j] << std::endl;
                return true; //Debug return true;
            }
    }

    return false; //Debug: Origin return false;
}

