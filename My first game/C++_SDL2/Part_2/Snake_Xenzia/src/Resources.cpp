//Resources [Sources]
#include "Resources.hpp"

//Include Headers
#include "TextureManager.hpp"

//class Resources
//static
    SDL_Texture* Resources::tilemap;
    SDL_Rect Resources::tilemap_sprite[TILE_MAP_VALUE_TOTAL];

    SDL_Texture* Resources::snake;
    SDL_Rect Resources::snake_sprite[SNAKE_VALUE_TOTAL];

    SDL_Texture* Resources::fruit;

    SDL_Renderer* Resources::renderer;

    Console Resources::console("Resources");


// Resources::Resources()
// {
//     tilemap = NULL;
//     snake = NULL;
//     fruit = NULL;
//     renderer = NULL;
// }

// Resources::~Resources()
// {
//     tilemap = NULL;
//     snake = NULL;
//     fruit = NULL;
//     renderer = NULL;
// }

void Resources::init(SDL_Renderer* _renderer)
{
    renderer = _renderer;

    console.writeLine("Initilized");
}   

void Resources::load()
{
    //tile_map
    tilemap = TextureManager::load("res/tilemap.png");

    tilemap_sprite[GRASS] = {0, 0, PIXEL, PIXEL};
    tilemap_sprite[DIRT] = {PIXEL, 0, PIXEL, PIXEL};

    //snake
    snake = TextureManager::load("res/snakes.png");
    //head
    snake_sprite[SNAKE_HEAD_UP] = {0, 0, PIXEL, PIXEL};
    snake_sprite[SNAKE_HEAD_DOWN] = {0, PIXEL, PIXEL, PIXEL};
    snake_sprite[SNAKE_HEAD_LEFT] = {0, PIXEL*2, PIXEL, PIXEL};
    snake_sprite[SNAKE_HEAD_RIGHT] = {0, PIXEL*3, PIXEL, PIXEL};

    //body
    snake_sprite[SNAKE_BODY_UP] = {PIXEL, 0, PIXEL, PIXEL};
    snake_sprite[SNAKE_BODY_DOWN] = {PIXEL, PIXEL, PIXEL, PIXEL};
    snake_sprite[SNAKE_BODY_LEFT] = {PIXEL, PIXEL*2, PIXEL, PIXEL};
    snake_sprite[SNAKE_BODY_RIGHT] = {PIXEL, PIXEL*3, PIXEL, PIXEL};

    //tail
    snake_sprite[SNAKE_TAIL_UP] = {PIXEL*4, 0, PIXEL, PIXEL};
    snake_sprite[SNAKE_TAIL_DOWN] = {PIXEL*4, PIXEL, PIXEL, PIXEL};
    snake_sprite[SNAKE_TAIL_LEFT] = {PIXEL*4, PIXEL*2, PIXEL, PIXEL};
    snake_sprite[SNAKE_TAIL_RIGHT] = {PIXEL*4, PIXEL*3, PIXEL, PIXEL};

    //conner
    snake_sprite[SNAKE_CORNER_RIGHT_UP] = {PIXEL*2, 0, PIXEL, PIXEL}; 
    snake_sprite[SNAKE_CORNER_LEFT_UP] = {PIXEL*2, PIXEL, PIXEL, PIXEL};
    snake_sprite[SNAKE_CORNER_UP_LEFT] = {PIXEL*2, PIXEL*2, PIXEL, PIXEL};
    snake_sprite[SNAKE_CORNER_DOWN_LEFT] = {PIXEL*2, PIXEL*3, PIXEL, PIXEL};

    snake_sprite[SNAKE_CORNER_RIGHT_DOWN] = {PIXEL*3, 0, PIXEL, PIXEL};
    snake_sprite[SNAKE_CORNER_LEFT_DOWN] = {PIXEL*3, PIXEL, PIXEL, PIXEL};
    snake_sprite[SNAKE_CORNER_UP_RIGHT] = {PIXEL*3, PIXEL*2, PIXEL, PIXEL};
    snake_sprite[SNAKE_CORNER_DOWN_RIGHT] = {PIXEL*3, PIXEL*3, PIXEL, PIXEL};

    //fruit
    fruit = TextureManager::load("res/Fruit.png");

    console.writeLine("Loaded Resources!");
}

SDL_Texture* Resources::getTexture(RESOURCES_VALUE value)
{
    SDL_Texture* tmpTexture = NULL;

    switch (value)
    {
    case TILE_MAP_VAL:
        tmpTexture = tilemap;
        break;
    
    case SNAKE_VAL:
        tmpTexture = snake;
        break;

    case FRUIT_VAL:
        tmpTexture = fruit;
        break;
    default:
        break;
    }

    return tmpTexture;
}

SDL_Rect Resources::getSprite(SNAKE_VALUE value)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = snake_sprite[value];
    return tmpRect;
}

/*
SDL_Rect Resources::getSprite(RESOURCES_VALUE value)
{
    
}
*/

SDL_Rect Resources::getSprite(TILE_MAP_VALUE value)
{
    SDL_Rect tmpRect = {0, 0, 0, 0};
    tmpRect = tilemap_sprite[value];
    return tmpRect;
}

void Resources::free()
{
    console.writeLine("Free memory. . .");

    SDL_DestroyTexture(tilemap);
    SDL_DestroyTexture(snake);
    SDL_DestroyTexture(fruit);
    tilemap = NULL;
    snake = NULL;
    fruit = NULL;

    renderer = NULL;
}