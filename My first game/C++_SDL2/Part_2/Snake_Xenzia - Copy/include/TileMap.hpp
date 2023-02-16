//TileMap [Head]
#ifndef TILEMAP_HPP
#define TILEMAP_HPP

//Include Headers
#include "Resources.hpp"

#include <string>

//class TileMap
class TileMap
{
public:
    TileMap(std::string path, SDL_Renderer* _renderer, int _w, int _h);
    void load(std::string path);
    bool canRender();
    void render();
    void destroy();
private:
    int width, height;

    bool checkMap;

    int** data;

    SDL_Rect scrRect, destRect;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
};

#endif //TILEMAP_HPP