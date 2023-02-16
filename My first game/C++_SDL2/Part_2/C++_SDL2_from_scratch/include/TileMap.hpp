//TileMap [Header]
#ifndef TileMap_hpp
#define TileMap_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TileMap
{
    public:
        TileMap();
        ~TileMap();

        void DrawMap();
        void LoadMap(int arr[15][20]);
    private:
        SDL_Rect srcRect, destRect;
        SDL_Texture* dirt;
        SDL_Texture* water;
        SDL_Texture* grass;

        int Map[15][20];
};

#endif //TileMap_hpp