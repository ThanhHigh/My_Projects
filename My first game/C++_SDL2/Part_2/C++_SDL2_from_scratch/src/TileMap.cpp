//TileMap [Source]
#include "TileMap.hpp"
#include "TextureManager.hpp"

//Project source
#include "TextureManager.hpp"

//Variables
//Level 1
int lv1[15][20] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0},
    {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0},
    {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0},
    {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0},
    {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0},
    {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0},
    {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0},
    {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0},
    {0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


TileMap::TileMap()
{
    dirt = TextureManager::loadTexture("bin/debug/res/dirt.png");
    water = TextureManager::loadTexture("bin/debug/res/water.png");
    grass = TextureManager::loadTexture("bin/debug/res/grass.png");

    //Load Map
    LoadMap(lv1);

    //Source and Destination
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 32;
    srcRect.h = 32;

    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

TileMap::~TileMap()
{
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(water);
    SDL_DestroyTexture(dirt);
}

void TileMap::LoadMap(int arr[15][20])
{
    for (int row = 0; row < 15; row++)
    {
        for (int col = 0; col < 20; col++)
            Map[row][col] = arr[row][col];
    }
}

void TileMap::DrawMap()
{
    int type = 0;

    for (int row = 0; row < 15; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            type = Map[row][col];

            destRect.x = col * 32;

            destRect.y = row * 32;

            switch (type)
            {
            case 0:
                TextureManager::Draw(water, srcRect, destRect);
                break;
            case 1:
                TextureManager::Draw(dirt, srcRect, destRect);
                break;
            case 2:
                TextureManager::Draw(grass, srcRect, destRect);
                break;
            default:
                break;
            }
        }
    }
}
