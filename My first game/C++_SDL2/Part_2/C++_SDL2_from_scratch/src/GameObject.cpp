//GameObject [Source]
#include "GameObject.hpp"
#include "TextureManager.hpp"
//Project lib
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//C++ lib
#include <string>

GameObject::GameObject(std::string texturesheet, SDL_Renderer* ren, int x, int y)
{
    renderer = ren;
    objTexture = TextureManager::loadTexture(texturesheet, ren);

    xpos = x;
    ypos = y;
}

GameObject::~GameObject()
{
    //Destroy Renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    
    //Destroy Texture & Rect
    SDL_DestroyTexture(objTexture);
    objTexture = NULL;
}

void GameObject::Update()
{
    //Motion
    xpos++;
    ypos++;

    //Rect
    //SrcRect
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 1024;
    srcRect.h = 1024;

    //DestRect
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 32 * 3;
    destRect.h = 32 * 3;
}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

