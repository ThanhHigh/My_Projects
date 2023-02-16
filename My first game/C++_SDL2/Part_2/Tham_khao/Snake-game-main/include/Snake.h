///Snake [Header]
#ifndef SNAKE_H_
#define SNAKE_H_

//include SDL library
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Project headers
#include "TextureManager.h"
#include "Direction.h"

//C++ library
#include <string>

const int MAX_TAIL = 20*15;

///Snake class
class Snake
{
    public:
        Snake(int x, int y, int w, int h);
        ~Snake();

        void update();
        void setDir(DIRECTION flag);
        void moving();
        void render();
        void eatFruit();

        int get_tile_x();
        int get_tile_y();

    private:
        DIRECTION cur_dir;

        bool eatenFruit;
        int waitTime;
        int width, height;
        int tail;
        int tile_x[MAX_TAIL], tile_y[MAX_TAIL];
        int screen_x[MAX_TAIL], screen_y[MAX_TAIL];
        DIRECTION dir_at[MAX_TAIL];

        SDL_Texture* texture;
        SDL_Rect srcRect, destRect;
};

#endif // SNAKE_H_
