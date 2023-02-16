//Engine [Header]
#ifndef ENGINE_HPP
#define ENGINE_HPP

//Include Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Console.hpp"
#include "Playing.hpp"

#include <string>

//class Engine
class Engine
{
public:
    Engine();
    ~Engine();

    static void init(const std::string _title, const int _w, const int _h);
    static bool isRunning();
    static void handleEvent();
    static void update();
    static void render();
    static int get_width();
    static int ger_height();
    static void close();

    static int width, height;
    static SDL_Renderer* renderer;
private:
    static SDL_Window* window;

    static SDL_Texture* texture;
    static Console console;
    static Playing playing;

    static bool running;
};





#endif //ENGINE_HPP