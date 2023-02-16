//Fruit [Head]
#ifndef FRUIT_HPP
#define FRUIT_HPP

//Include Headers
#include <SDL2/SDL.h>

//class Fruit
class Fruit
{
public:
    Fruit(int x, int y, int w, int h);
    ~Fruit();

    void generate();
    void load(); //= Hàm update()  của anh Bá
    bool isEaten();
    void render();
    int get_tile_x();
    int get_tile_y();

private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    bool isEatened;

    int screen_x, screen_y;
    int tile_x, tile_y;
    int width, height;

};

#endif //FRUIT_HPP