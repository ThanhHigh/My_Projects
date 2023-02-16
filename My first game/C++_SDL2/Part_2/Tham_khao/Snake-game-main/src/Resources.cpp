///Resources [Source]
#include "Resources.h"

//Project headers
#include "TextureManager.h"

//Static 
/* Assume: Set up for private static val can work correctly between methods in class Resources  */
SDL_Texture* Resources::tile_map;
SDL_Rect Resources::map_sprite[TILE_MAP_COUNT];
SDL_Texture* Resources::snake;
SDL_Rect Resources::snake_sprite[SNAKE_COUNT];
SDL_Texture* Resources::fruit;

SDL_Renderer* Resources::renderer;

Console Resources::console("Resources");

///Resources class
void Resources::init(SDL_Renderer* _renderer)
{
    renderer = _renderer;

    console.writeLine("Init done!");
}

void Resources::load()
{
    //tile_map
    tile_map = TextureManager::load("res/tileMap.png");

    map_sprite[GRASS] = {0, 0, PIXEL, PIXEL};
    map_sprite[DIRT] = {PIXEL, 0, PIXEL, PIXEL};

    //snake
    snake = TextureManager::load("res/snakes.png");

    //Head
    snake_sprite[SNAKE_HEAD_UP] = {0, 0, PIXEL, PIXEL};  /* Hàm snake_sprite, map_sprite, fruit_sprite trả về các SDL_Rect */
    snake_sprite[SNAKE_HEAD_DOWN] = {0, PIXEL, PIXEL, PIXEL};
    snake_sprite[SNAKE_HEAD_LEFT] = {0, PIXEL*2, PIXEL, PIXEL};
    snake_sprite[SNAKE_HEAD_RIGHT] = {0, PIXEL*3, PIXEL, PIXEL};

    //Body
    snake_sprite[SNAKE_BODY_UP] = {PIXEL, 0, PIXEL, PIXEL};
    snake_sprite[SNAKE_BODY_DOWN] = {PIXEL, PIXEL, PIXEL, PIXEL};
    snake_sprite[SNAKE_BODY_LEFT] = {PIXEL, PIXEL*2, PIXEL, PIXEL};
    snake_sprite[SNAKE_BODY_RIGHT] = {PIXEL, PIXEL*3, PIXEL, PIXEL};

    //Corner
    snake_sprite[SNAKE_CORNER_RIGHT_UP] = {PIXEL*2, 0, PIXEL, PIXEL}; /* > ^ */
    snake_sprite[SNAKE_CORNER_LEFT_UP] = {PIXEL*2, PIXEL, PIXEL, PIXEL}; /* < ^ */
    snake_sprite[SNAKE_CORNER_UP_LEFT] = {PIXEL*2, PIXEL*2, PIXEL, PIXEL}; /* ^ < */
    snake_sprite[SNAKE_CORNER_DOWN_LEFT] = {PIXEL*2, PIXEL*3, PIXEL, PIXEL}; /* v < */

    snake_sprite[SNAKE_CORNER_RIGHT_DOWN] = {PIXEL*3, 0, PIXEL, PIXEL};
    snake_sprite[SNAKE_CORNER_LEFT_DOWN] = {PIXEL*3, PIXEL, PIXEL, PIXEL};
    snake_sprite[SNAKE_CORNER_UP_RIGHT] = {PIXEL*3, PIXEL*2, PIXEL, PIXEL};
    snake_sprite[SNAKE_CORNER_DOWN_RIGHT] = {PIXEL*3, PIXEL*3, PIXEL, PIXEL};

    //Tail
    snake_sprite[SNAKE_TAIL_UP] = {PIXEL*4, 0, PIXEL, PIXEL};
    snake_sprite[SNAKE_TAIL_DOWN] = {PIXEL*4, PIXEL, PIXEL, PIXEL};
    snake_sprite[SNAKE_TAIL_LEFT] = {PIXEL*4, PIXEL*2, PIXEL, PIXEL};
    snake_sprite[SNAKE_TAIL_RIGHT] = {PIXEL*4, PIXEL*3, PIXEL, PIXEL};

    //fruit
    fruit = TextureManager::load("res/fruit.png");

    console.writeLine("Load textures done!");
}

SDL_Texture* Resources::getTexture(RESOURCES_VALUE value)
{
    SDL_Texture* tmpTexture = NULL;
    switch (value)
    {
        //tile map
        case TILE_MAP:
        case GRASS_VAL:
        case DIRT_VAL:
            tmpTexture = tile_map;
            break;

        //snake
        case SNAKE_VAL:
            tmpTexture = snake;
            break;

        //fruit
        case FRUIT_VAL:
            tmpTexture = fruit;
            break;
    }
    return tmpTexture;
}

SDL_Rect Resources::getSprite(RESOURCES_VALUE value)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    switch (value)
    {
        //tile map
        case TILE_MAP:
            break;
        case GRASS_VAL:
            tmpRect = map_sprite[GRASS];
            break;
        case DIRT_VAL:
            tmpRect = map_sprite[DIRT];
            break;

        //snake
        case SNAKE_VAL:
            break;

        //fruit
        case FRUIT_VAL:
            break;
    }
    return tmpRect;
}

SDL_Rect Resources::getSprite(SNAKE_VALUE value)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = snake_sprite[value];
    return tmpRect;
}

void Resources::free()
{
    console.writeLine("Free memory. . .");

    SDL_DestroyTexture(tile_map); /* Hủy tất cả các texture */
    SDL_DestroyTexture(snake);
    SDL_DestroyTexture(fruit);
    tile_map = NULL; /* gán các con trỏ về null */
    snake = NULL;
    fruit = NULL;

    renderer = NULL;
}
