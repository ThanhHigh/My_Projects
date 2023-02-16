//Collision [Header]
#ifndef Collision_hpp
#define Collision_hpp

//SDL lib
#include <SDL2/SDL.h>



class Collision
{
    public:
        static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};

#endif //Collision_hpp