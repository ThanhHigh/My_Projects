///Texture Manager [Source]
#include "TextureManager.h"

#include "Engine.h"

///TextureManager class
SDL_Texture* TextureManager::load(std::string path)
{
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(Engine::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tmpTexture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
    SDL_RenderCopy(Engine::renderer, texture, &srcRect, &destRect);
}
