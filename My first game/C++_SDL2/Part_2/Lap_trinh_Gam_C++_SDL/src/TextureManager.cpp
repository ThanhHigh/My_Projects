#include "TextureManager.hpp"
#include "Engine.hpp"

bool TextureManager::loadTexture(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surface);
    if (texture == nullptr)
    {
        SDL_Log("Failed to load texture: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip filp)
{
    SDL_Rect srcRect = {0, 0, width, height},
             destRect = {x, y, width, height};
    
    SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(),m_TextureMap[id], &srcRect, &destRect, 0, nullptr, filp);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip filp)
{
    SDL_Rect srcRect = {width*frame, (row-1)*height, width, height},
             destRect = {x, y, width, height};
    
    SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(),m_TextureMap[id], &srcRect, &destRect, 0, nullptr, filp);
    
}

void TextureManager::dropTexture(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    //remove object texture from map
    m_TextureMap.erase(id);
}


void TextureManager::cleanTexture()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    m_TextureMap.clear();

    SDL_Log("Texture Map Clean!");
}