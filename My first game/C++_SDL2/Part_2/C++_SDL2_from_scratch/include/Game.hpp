//Game [Header]
#ifndef Game_hpp
#define Game_hpp

//Project Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//C++ lib
#include <string>

class Game
{
    public:
        Game();
        ~Game();

        void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen);

        void HandleEvent();
        void Update();
        void Render();
        void Clean();

        bool running();

        static SDL_Renderer* renderer;

        static SDL_Event event;
    private:
        bool isRunning = true;

        SDL_Window* window = NULL;
};

#endif //Game_hpp