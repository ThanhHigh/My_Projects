//Texture [Header]
#ifndef Texture_hpp
#define Texture_hpp

//Include Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "Console.hpp"

class Texture
{
public:

    Texture();
    ~Texture();

    //init
    void init(SDL_Renderer* _renderer);

    //load:
    SDL_Texture* load(const std::string path);

private:
    SDL_Renderer* renderer;

    Console* console;
    
};


#endif //Texture_hpp