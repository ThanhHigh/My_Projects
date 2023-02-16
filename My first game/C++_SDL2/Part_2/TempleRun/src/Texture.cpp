//Texture [Source]
#include "Texture.hpp"

//Include Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Console.hpp"

//Texture class
//Constructor
Texture::Texture(/* args */)
{
    
}

//Deconstructor
Texture::~Texture()
{

}

//Function
//init
//ini
void Texture::init(SDL_Renderer* _renderer)
{
    console = new Console("Texture");
    renderer = _renderer;
    
    console->writeLine("Initilize texture sub-system.");
}

//load:
SDL_Texture* Texture::load(const std::string path)
{
    console->writeLine("Loading file: " + path);
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());

    SDL_Texture* tmpTexture = NULL;

    if (tmpSurface == NULL)
    {
        //Error:
        console->logError("Could not load file: " + path, ERROR_FLAGS::IMG_ERROR);
        return tmpTexture;
    }

    SDL_CreateTextureFromSurface(renderer, tmpSurface);

    if (tmpSurface == NULL)
    {
        //Error:
        console->logError("Could not create texture from surface " + path, ERROR_FLAGS::IMG_ERROR);
        return tmpTexture;
    }

    //Free
    SDL_FreeSurface(tmpSurface);
    tmpSurface = NULL;

    return tmpTexture;
}

