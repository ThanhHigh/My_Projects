#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>

class TextureManager
{
public:
    std::map<std::string, int> m_getTextureHeight;
    std::map<std::string, int> m_getTextureWidth;

    static TextureManager* getInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();}

    bool loadTexture(std::string id, std::string filename);
    bool loadTextureTex(std::string id, std::string content, TTF_Font* m_Font, SDL_Colour _texColour);
    bool parseTextures(std::string sources);
    void dropTexture(std::string id);
    void cleanTexture();

    void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip filp = SDL_FLIP_NONE);
    void drawtile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawBG(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawText(std::string id, std::string content, int x, int y, SDL_Colour textColour, TTF_Font* ttf_font, SDL_Rect* clip = NULL, double angle = 0.0 , SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    TextureManager(){}
    std::map<std::string, SDL_Texture*> m_TextureMap;

    static TextureManager* s_Instance;
};

#endif //TextureManager_hpp