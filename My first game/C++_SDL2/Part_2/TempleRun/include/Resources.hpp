//Resources [Header]
#ifndef Resources_hpp
#define Resources_hpp

//Include Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Console.hpp"
#include "Texture.hpp"

#include <string>

//Viewport

//Resources
enum RESOURCES_TYPE
{
    BACKGROUND = 0,
    BUTTON,
    BUTTON_SETTING,
    RESOURCES_TYPE_TOTAL
};

//background
const int BACKGROUND_WIDTH = 1280;
const int BACKGROUND_HEIGHT = 720;

enum BACKGROUND_TYPE
{
    BACKGROUND_MENU = 0,
    BACKGROUND_RESUME,
    BACKGROUND_SETTING,
    BACKGROUND_SAVE_SETTING,
    BACKGROUND_HOW_TO_PLAY,
    BACKGROUND_GAME_OVER,
    BACKGROUND_WIN_GAME,
    BACKGROUND_HIGH_SCORE,
    BACKGROUND_EXIT_GAME,
    BACKGROUND_ABOUT,
    BACKGROUND_TYPE_TOTAL
};

//button:

//setting_button:

//player

//object:



class Resources
{
public:

    Resources();
    ~Resources();

    void init(Texture* _texture);

    void load();

    void create();

    void free();

    void close();

private:
    //Console
    Console* console;

    //Texture
    Texture* texture = NULL;

    //Textures
    SDL_Texture* background = NULL;
};



#endif //Resources_hpp