//Playing [Header]
#ifndef PLAYING_HPP
#define PLAYING_HPP

//Include Headers
#include <SDL2/SDL.h>

#include "Console.hpp"
#include "Snake.hpp"
#include "Fruit.hpp"
#include "TextureManager.hpp"
#include "Resources.hpp"
#include "TileMap.hpp"

//Playing class
class Playing
{

public:
    Playing();
    ~Playing();

    void init(SDL_Window* _window, SDL_Renderer* _renderer);
    void loop();
    void keyPress(int key_sym);
    void keyRelease(int key_sym);
    void render();
    void destroy();
private:
    Console* console;
    SDL_Window* window;
    SDL_Renderer* renderer;

    int *width, *height;

    TileMap* tilemap;
    Snake* snake;
    Fruit* fruit;
};  



#endif //PLAYING_HPP