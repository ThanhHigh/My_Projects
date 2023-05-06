#include "TextureManager.hpp"
#include "Engine.hpp"
#include "Camera.hpp"

#include "tinyxml.h"

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

bool TextureManager::loadTextureTex(std::string id, std::string content, TTF_Font* m_Font, SDL_Colour _texColour)
{
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( m_Font, content.c_str(), _texColour );
    SDL_Texture* texture;
    if( textSurface == NULL )
    {
       std::cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError() << std::endl;
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( Engine::GetInstance()->getRenderer(), textSurface );

        if (texture == nullptr) 
        {
            std::cout << "Unable to create texture from rendered text! SDL Error: " << std::endl;
        }
        else
        {
            //Get text dimension
            m_getTextureHeight[id] = textSurface->h;
            m_getTextureWidth[id] = textSurface->w;
        }
    }
    m_TextureMap[id] = texture;
    return texture != NULL;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip filp)
{
    Vector2D cam = Camera::getInstance()->getPosition() * 0.5;
    SDL_Rect srcRect = {0, 0, width, height},
             destRect = {x - cam.X, y - cam.Y, width, height};
    
    SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(),m_TextureMap[id], &srcRect, &destRect, 0, nullptr, filp);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip filp)
{
    Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect srcRect = {width*frame, (row-1)*height, width, height},
             destRect = {x - cam.X, y - cam.Y, width, height};
    
    SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(),m_TextureMap[id], &srcRect, &destRect, 0, nullptr, filp);
    
}
void TextureManager::drawtile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect dstRect = {x - cam.X, y - cam.Y, tilesize, tilesize};
    SDL_Rect srcRect = {tilesize*frame, tilesize*(row) /* row - 1 in tutorial */, tilesize, tilesize};
    SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::drawBG(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{ 
    SDL_Rect srcRect = {0, 0, width, height},
             destRect = {x, y, width, height};

    SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::drawText(std::string id, std::string content, int x, int y, SDL_Colour textColour, TTF_Font* ttf_font, SDL_Rect* clip, double angle , SDL_RendererFlip flip)
{
    //Render text
    if (!(loadTextureTex(id, content, ttf_font, textColour)))
    {
        std::cout << "Failed to render text texture!" << std::endl;
    }
    //Set rendering space and render to screen
    
    SDL_Rect renderQuad = { x, y, m_getTextureWidth[id], m_getTextureHeight[id] };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    //Render to screen
    SDL_RenderCopyEx( Engine::GetInstance()->getRenderer(), m_TextureMap[id], clip, &renderQuad, angle, nullptr, flip );
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

    SDL_Log("Texture Clean!");
}


bool TextureManager::parseTextures(std::string sources)
{
    TiXmlDocument xml;
    xml.LoadFile(sources);
    if (xml.Error())
    {
        std::cout << "Failed to Load: " << sources << " " << xml.ErrorDesc() << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("texture"))
        {
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            loadTexture(id, src);
        }
    }
    std::cout << "Textures Parse success!" << std::endl;
    return true;
}