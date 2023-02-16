//Snake [Source]
#include "Snake.hpp"

//Include Headers
#include "Resources.hpp"
#include "Engine.hpp"

//Const for snake sprite
const SNAKE_VALUE snake_flag[4][4] = {
    SNAKE_BODY_UP, SNAKE_UNSET, SNAKE_CORNER_UP_RIGHT, SNAKE_CORNER_UP_LEFT,
    SNAKE_UNSET, SNAKE_BODY_DOWN, SNAKE_CORNER_DOWN_RIGHT, SNAKE_CORNER_DOWN_LEFT,
    SNAKE_CORNER_RIGHT_UP, SNAKE_CORNER_RIGHT_DOWN, SNAKE_BODY_RIGHT, SNAKE_UNSET,
    SNAKE_CORNER_LEFT_UP, SNAKE_CORNER_LEFT_DOWN, SNAKE_UNSET, SNAKE_BODY_LEFT
};

const int GAMESTART_LENGTH = 2; //has to smaller than MAX_LENGTH = 20

Snake::Snake(int x, int y, int w, int h)
{
    texture = Resources::getTexture(SNAKE_VAL);

    //speed
    waitTime = 0;

    tail = GAMESTART_LENGTH; //length snake when game start
    eatened = false;

    //[0][0] is head of snake
    //snake control by array tile_x and tile_y
    bool checktail = true;
    int tmplength = GAMESTART_LENGTH;
    do
    {
        if (checktail)
        {
            tile_x[tmplength - 1] = x;
            tile_y[tmplength - 1] = y;
            checktail = false;
        }
        else
        {
            tile_x[tmplength - 1] = tile_x[tmplength] + 1;
            tile_y[tmplength - 1] = tile_y[tmplength];
        }        
        tmplength--;
    } while (tmplength > 0);

    update();

    width = w;
    height = h;

    //scrRect is head of snake in currently snakes.png
    scrRect = {0, 0, width, height}; 
}

Snake::~Snake()
{
    SDL_DestroyTexture(texture);
    texture = NULL;
}

void Snake::moving()
{

}

void Snake::update()
{

}

void Snake::render()
{
    // int i;
    {
        // int f1 = dir_at[i] - 1;
        // int f2 = dir_at[i+1] - 1;
        // scrRect = Resources::getSprite(snake_flag[f1][f2]);
    }
}
int Snake::get_tile_x()
{
    return tile_x[0];
}
int Snake::get_tile_y()
{
    return tile_y[0];
}
bool Snake::eaten()
{
    return eatened;
}
