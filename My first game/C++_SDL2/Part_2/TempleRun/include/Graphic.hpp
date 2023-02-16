//Graphic [Header]
#ifndef Graphic_hpp
#define Graphic_hpp

//Include Header
#include "Console.hpp"
#include "Resources.hpp"
#include "Texture.hpp"

#include <SDL2/SDL.h>

class Graphic
{

public:

    Graphic();
    ~Graphic();

    //function
    //init
    void init();

    //clearscreen

    //draw

    //render text

    //set viewport

    //set texture aphal blending

    //close

private:
    //Renderer
    SDL_Renderer* renderer;

    //Console
    Console* console;

    //Resources
    Resources* resources;

    //Texture
    Texture* texture;

    //System value

};



#endif //Graphic_hpp