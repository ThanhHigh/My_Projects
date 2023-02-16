///Tile Map [Header]
#ifndef TILE_MAP_H_
#define TILE_MAP_H_

//Include SDL libraries
#include <SDL2/SDL.h>

//Project headers
#include "TextureManager.h"

//C++ librarr
#include <string>

///Tile Map class
class TileMap
{
    public:
        TileMap(std::string path, SDL_Renderer* _renderer, int w, int h); /* Hàm khởi tạo kết hợp với init map */
        void load(std::string path); /* load tile của map từ file path */
        bool canRender(); /* check xem có thể render không */
        void render(); /* Nếu có thì render */

    private:
        int width, height; /* Thông số của map */
        int **data; /* ??? */

        bool checkMap; /* Kiểm tra xem có thể render map hay ko */

        SDL_Texture* texture; /* Render thì phải có texture */
        SDL_Rect srcRect, destRect; /* scrRect và desrect */
        SDL_Renderer* renderer;
};

#endif // TILE_MAP_H_
