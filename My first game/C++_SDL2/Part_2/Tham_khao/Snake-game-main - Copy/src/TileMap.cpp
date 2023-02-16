///Tile Map [Source]
#include "TileMap.h"

//C++ library
#include <fstream>
#include <iostream>

//Project headers
#include "Resources.h"

///Tile Map class
TileMap::TileMap(std::string path, SDL_Renderer* _renderer, int w, int h) /* Hàm khởi tạo */ /* Đọc map từ file dat vào */
{
    renderer = _renderer;

    width = w;
    height = h; /* Set up value */

    texture = Resources::getTexture(TILE_MAP);

    data = new int*[width];
    for (int row = 0; row < width; row++)
        data[row] = new int[height];

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
    for (int row = 0; row < width; row++)
        for (int column = 0; column < height; column++)
        {
            destRect = {column*PIXEL, row*PIXEL, PIXEL, PIXEL};
            switch (data[row][column])
            {
                case 0:
                    srcRect = Resources::getSprite(GRASS_VAL);
                    break;
                case 1:
                    srcRect = Resources::getSprite(DIRT_VAL);
                    break;
            }
            TextureManager::draw(texture, srcRect, destRect);
        }
}
