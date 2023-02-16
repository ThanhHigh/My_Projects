///Resources [Header]
#ifndef RESOURCES_H_
#define RESOURCES_H_

//Include SDL library
#include <SDL2/SDL.h>

//Project headers
#include "Console.h"

enum RESOURCES_VALUE
{
    //tile map
    TILE_MAP = 0,
    GRASS_VAL,
    DIRT_VAL,

    //snake
    SNAKE_VAL,

    //fruit
    FRUIT_VAL
};

enum TILE_MAP_VALUE
{
    GRASS = 0,
    DIRT,
    TILE_MAP_COUNT
};

enum SNAKE_VALUE
{
    SNAKE_UNSET = -1,
    SNAKE_HEAD_UP,
    SNAKE_HEAD_DOWN,
    SNAKE_HEAD_LEFT,
    SNAKE_HEAD_RIGHT,
    SNAKE_BODY_UP,
    SNAKE_BODY_DOWN,
    SNAKE_BODY_LEFT,
    SNAKE_BODY_RIGHT,
    SNAKE_CORNER_RIGHT_UP,
    SNAKE_CORNER_RIGHT_DOWN,
    SNAKE_CORNER_LEFT_UP,
    SNAKE_CORNER_LEFT_DOWN,
    SNAKE_CORNER_UP_LEFT,
    SNAKE_CORNER_UP_RIGHT,
    SNAKE_CORNER_DOWN_LEFT,
    SNAKE_CORNER_DOWN_RIGHT,
    SNAKE_TAIL_UP,
    SNAKE_TAIL_DOWN,
    SNAKE_TAIL_LEFT,
    SNAKE_TAIL_RIGHT,
    SNAKE_COUNT
};

enum FRUIT_VALUE
{
    FRUIT,
    FRUIT_COUNT
};

const int PIXEL = 32;

///Resources class
class Resources
{
    public:

        /* Does not have constructor and deconstructor functions */

        static void init(SDL_Renderer* _renderer); 
        static void load();
        static SDL_Texture* getTexture(RESOURCES_VALUE value);
        static SDL_Rect getSprite(RESOURCES_VALUE value);
        static SDL_Rect getSprite(SNAKE_VALUE value);
        static void free();

    private:
        //static void loadFile(std::string path);

        static SDL_Texture* tile_map;
        static SDL_Rect map_sprite[TILE_MAP_COUNT];
        static SDL_Texture* snake;
        static SDL_Rect snake_sprite[SNAKE_COUNT];
        static SDL_Texture* fruit;

        static SDL_Renderer* renderer;

        static Console console;
};

#endif // RESOURCES_H_
