//TextureManager [Source]
#include "TextureManager.hpp"
#include "Game.hpp"

//Project Headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* TextureManager::loadTexture (const std::string path, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(ren, tempSurface);

    SDL_FreeSurface(tempSurface);
    
    return tempTexture;
}

SDL_Texture* TextureManager::loadTexture(const std::string path)
{
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

    SDL_FreeSurface(tempSurface);
    
    return tempTexture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect scr, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, &scr, &dest);
}