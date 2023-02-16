//Engine [Header]
#ifndef Engine_hpp
#define Engine_hpp

//Include library
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Console.hpp"
#include "System.hpp"
#include "StateManager.hpp"
class Engine
{
    public:
        //Constructor:
        Engine();

        //Deconstructor:
        ~Engine();

        //Function:
        //Initilize
        void init(const std::string _title, const int _width, const int _height);

        void handleEvent();

        bool isRunning();

        void render();

        void loop();

        void close();
    private:
        //Window
        SDL_Window* window;
        SDL_Renderer* renderer;

        //Information:
        int width, height;
        bool running;
        std::string title;

        //Console
        Console* console;

        //System
        System* system;

};

#endif //Engine_hpp