#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

class TextureManager
{
public:
    static TextureManager* getInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();}

    bool loadTexture(std::string id, std::string filename);
    void dropTexture(std::string id);
    void cleanTexture();

    void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip filp = SDL_FLIP_NONE);
    void drawtile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    TextureManager(){}
    std::map<std::string, SDL_Texture*> m_TextureMap;
    static TextureManager* s_Instance;
};

#endif //TextureManager_hpp