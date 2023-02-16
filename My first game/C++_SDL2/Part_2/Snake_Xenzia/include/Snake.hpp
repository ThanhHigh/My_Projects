//Snake [Head]
#ifndef SNAKE_HPP
#define SNAKE_HPP

//Include Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TextureManager.hpp"
#include "Direction.hpp"

#include <string>

//Const
const int MAX_LENGTH = 20;

//class Snake
class Snake
{

public:
    Snake(int x, int y, int w, int h);
    ~Snake();

    void setDir(DIRECTION flag);
    void moving();
    void update();
    void render();
    int get_tile_x();
    int get_tile_y();
    bool eaten();

private:

    int waitTime;
    int tail;
    int width, height;
    int screen_x[MAX_LENGTH], screen_y[MAX_LENGTH];
    int tile_x[MAX_LENGTH], tile_y[MAX_LENGTH];
    bool eatened;
    DIRECTION cur_dir;
    DIRECTION dir_at[MAX_LENGTH];
    
    SDL_Texture* texture;
    SDL_Rect scrRect, destRect;
};

#endif //SNAKE_HPP