//TextureManager [Source]
#include "TextureManager.hpp"

//Include Headers
#include "Engine.hpp"

//class TextureManager

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

SDL_Texture* TextureManager::load(std::string path)
{
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(Engine::renderer, tmpSurface);

    if (tmpTexture == NULL)
    {
        //Error:
    }
    else
    {
        SDL_FreeSurface(tmpSurface);   
    }
    return tmpTexture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{   
    SDL_RenderCopy(Engine::renderer, texture, &srcRect, &destRect);
}   