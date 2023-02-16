///Engine [Header]
#ifndef ENGINE_H_
#define ENGINE_H_

//Project headers
#include "Console.h"
#include "Playing.h"

//include SDL library
#include <SDL2/SDL.h>

//C++ library
#include <string>

///Engine class
class Engine
{
    public:
        Engine();
        ~Engine();
        static void init(int _width, int _height, std::string title);
        static bool isRunning();
        static void handleEvents();
        static void render();
        static void close();

        static SDL_Renderer* renderer; /* Tại sao lại cho hàm renderer là public */
        static int width, height;

    private:
        static SDL_Window* window;
        static bool running;

        static Console console;

        static Playing playing;

};

#endif // ENGINE_H_
