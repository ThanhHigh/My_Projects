#ifndef ENGINE_HPP
#define ENGINE_hPP

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine
{

public:
    //getInstance to make sure that it only has one Engine for whole program
    static Engine* GetInstance()
    {
        return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
    }
    bool initGame();
    void quitGame();
    void clearGame();

    void updateGame();
    void renderGame();
    void eventsGame();

    inline bool isRunningGame(){return m_Running;}
    inline SDL_Renderer* getRenderer(){return m_Renderer;}


private:
    Engine(){}

    static Engine* s_Instance;
    bool  m_Running;

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
};

#endif //ENGINE_HPP