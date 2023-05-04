//CollisionHandle_hpp
#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include <vector>

#include "SDL2/SDL.h"
#include "TileLayer.hpp"
#include "GameMap.hpp"

class CollisionHandler
{
    public:
        inline static CollisionHandler* getInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler();
        }

        bool MapCollision(SDL_Rect a); 
        bool checkCollision(SDL_Rect a, SDL_Rect b);
        void setCollisionMap(tileMap _tileMap, int _tilesize);

    private:
        static CollisionHandler* s_Instance;
        CollisionHandler();
        //Matrix to store tileID(it is tilemap but only for collision)
        tileMap m_CollisionTileMap;
        //Matrix of collision
        TileLayer* m_CollisionLayer;
        int m_MapTileSize;
        int m_MapWidth, m_MapHeight;

        friend class Engine;
};

#endif //CCOLLISIONHANDLER_HPP