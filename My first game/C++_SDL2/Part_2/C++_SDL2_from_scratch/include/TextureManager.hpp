// TextureManager [Head]
#ifndef TextureManager_hpp
#define TextureManager_hpp

//C++ project
#include <string>

//Project Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager
{
    public:
        static SDL_Texture* loadTexture(const std::string path, SDL_Renderer* ren);
        static SDL_Texture* loadTexture(const std::string path);
        static void Draw(SDL_Texture* tex, SDL_Rect scr, SDL_Rect dest);
    private:
};

#endif //TextureManager_hpp