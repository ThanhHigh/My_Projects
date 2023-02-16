//TileMap [Source]
#include "TileMap.hpp"

//Include Headers
#include <fstream>
#include "TextureManager.hpp"

TileMap::TileMap(std::string path, SDL_Renderer* _renderer, int _w, int _h)
{
    renderer = _renderer;

    width = _w;
    height = _h;

    texture = Resources::getTexture(TILE_MAP_VAL);

    //create map
    data = new int*[width];
    for (int row = 0; row < width; row++)
    {
        data[row] = new int[height];
    }

    //Read file map
    std::ifstream input(path);

    if (input.is_open())
    {
        for (int row = 0; row < width; row++)
            for (int column = 0; column < height; column++)
                input >> data[row][column];
        checkMap = true;
    }
    else
    {
        checkMap = false;
    }
}

void TileMap::load(std::string path)
{
    //Read file map
    std::ifstream input(path);

    if (input.is_open())
    {
        for (int row = 0; row < width; row++)
            for (int column = 0; column < height; column++)
                input >> data[row][column];
        checkMap = true;
    }
    else
    {
        checkMap = false;
    }
}

bool TileMap::canRender()
{
    return checkMap;
}

void TileMap::render()
{
    // if (!canRender()) return;

    for (int row = 0; row < width; row++)
    {
        for (int column = 0; column < height; column++)
        {
            destRect = {row*PIXEL, column*PIXEL, PIXEL, PIXEL};
            int tmp = data[row][column];
            switch (tmp)
            {
            case 0:
                scrRect = Resources::getSprite(GRASS);
                break;
            
            case 1:
                scrRect = Resources::getSprite(DIRT);
                break;
        
            default:
                break;
            }

            TextureManager::draw(texture, scrRect, destRect);
        }
    }
}

void TileMap::destroy()
{

}
