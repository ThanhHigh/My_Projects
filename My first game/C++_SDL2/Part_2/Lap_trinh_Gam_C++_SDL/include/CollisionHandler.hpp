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

        //Methods
        ////Collision any kind of objects and map, by box collider
        bool MapCollision(SDL_Rect a); 
        ////Check collision (ex: Player and Enemy)
        bool checkCollision(SDL_Rect a, SDL_Rect b);

    private:
        static CollisionHandler* s_Instance;
        CollisionHandler();
        //Matrix to store tileID(it is tilemap but only for collision)
        tileMap m_CollisionTileMap;
        //Matrix of collision
        TileLayer* m_CollisionLayer;
};

#endif //CCOLLISIONHANDLER_HPP