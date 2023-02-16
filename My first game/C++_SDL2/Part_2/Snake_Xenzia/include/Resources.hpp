//Resources [Header]
#ifndef RESOURCES_HPP
#define RESOURCES_HPP

//Include Header
#include "Console.hpp"

#include <SDL2/SDL.h>

enum RESOURCES_VALUE
{
    TILE_MAP_VAL = 0,
    SNAKE_VAL,
    FRUIT_VAL,
    RESOURCES_VAL_TOTAL
};

enum SNAKE_VALUE
{
    SNAKE_UNSET = -1,
    SNAKE_HEAD_UP,
    SNAKE_HEAD_DOWN,
    SNAKE_HEAD_RIGHT,
    SNAKE_HEAD_LEFT,
    SNAKE_BODY_UP,
    SNAKE_BODY_DOWN,
    SNAKE_BODY_RIGHT,
    SNAKE_BODY_LEFT,
    SNAKE_CORNER_UP_RIGHT,
    SNAKE_CORNER_UP_LEFT,
    SNAKE_CORNER_DOWN_RIGHT,
    SNAKE_CORNER_DOWN_LEFT,
    SNAKE_CORNER_RIGHT_UP,
    SNAKE_CORNER_RIGHT_DOWN,
    SNAKE_CORNER_LEFT_UP,
    SNAKE_CORNER_LEFT_DOWN,
    SNAKE_TAIL_UP,
    SNAKE_TAIL_DOWN,
    SNAKE_TAIL_RIGHT,
    SNAKE_TAIL_LEFT,
    SNAKE_VALUE_TOTAL
};

enum FRUIT_VALUE
{
    FRUIT_SET = 0,
    FRUIT_VALUE_TOTAL
};

enum TILE_MAP_VALUE
{
    GRASS = 0,
    DIRT,
    TILE_MAP_VALUE_TOTAL
};

const int PIXEL = 32;

class Resources
{
public:

    static void init(SDL_Renderer* _renderer);
    static void load();
    static SDL_Texture* getTexture(RESOURCES_VALUE value);
    static SDL_Texture* getTexture(TILE_MAP_VALUE value);
    static SDL_Rect getSprite(SNAKE_VALUE value);
    /* static SDL_Rect getSprite(RESOURCES_VALUE value); */
    static SDL_Rect getSprite(TILE_MAP_VALUE value);

    static void free();    
private:
    //map
    static SDL_Texture* tilemap;
    static SDL_Rect tilemap_sprite[TILE_MAP_VALUE_TOTAL];
    //snake
    static SDL_Texture* snake;
    static SDL_Rect snake_sprite[SNAKE_VALUE_TOTAL];
    //fruit
    static SDL_Texture* fruit;

    static SDL_Renderer* renderer;

    static Console console;

};

#endif //RESOURCES_HPP