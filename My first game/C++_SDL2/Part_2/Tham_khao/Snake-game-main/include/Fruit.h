///Fruit [Header]
#ifndef FRUIT_H_
#define FRUIT_H_

#include <SDL2/SDL.h>

///Fruit class
class Fruit
{
    public:
        Fruit(int x, int y, int w, int h);
        ~Fruit();

        bool isEaten();
        void setEaten();
        void update();
        void genarate();
        void render();

        int get_tile_x();
        int get_tile_y();

    private:
        bool eaten;
        int tile_x, tile_y;
        int screen_x, screen_y;
        int width, height;

        SDL_Texture* texture;
        SDL_Rect srcRect, destRect;
};

#endif // FRUIT_H_
