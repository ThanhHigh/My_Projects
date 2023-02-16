//TextureManager [Header]
#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

//Include headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

//Class TextureManager
class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
    static SDL_Texture* load(std::string path);
private:
    SDL_Texture* texture;
};


#endif //TEXTUREMANAGER_HPP
