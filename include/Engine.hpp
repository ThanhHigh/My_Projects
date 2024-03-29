#ifndef ENGINE_HPP
#define ENGINE_hPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "GameMap.hpp"
#include "MapParser.hpp"
#include "LevelPart.hpp"

// #define SCREEN_WIDTH 1344
// #define SCREEN_HEIGHT 768

// const int SCREEN_WIDTH = 1344;
// const int SCREEN_HEIGHT = 768;

const int TOTAL_MAP = 6;
const int TOTAL_LEVEL_MAP = 3;

class Engine
{

public:
    
    bool initGame();
    void quitGame();
    void clearGame();

    void updateGame();
    void renderGame();
    void eventsGame();
    void render_update_LevelPart();
    void updateLevelMap();
    bool createLevel();
    void mapPlayAgain();


    // void PopState();
    // void PushState(GameState* current);
    // void ChangeState(GameState* target);

    inline GameMap* getMap(){ return m_currMap; }
    inline bool isRunningGame(){ return m_Running; }
    inline SDL_Renderer* getRenderer(){ return m_Renderer; }
    //getInstance to make sure that it only has one Engine for whole program
    static Engine* GetInstance()
    {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
    }

    inline TTF_Font* getMenuFont(){ return m_MenuStartGameFont; }
    inline TTF_Font* getGameOverFont(){ return m_GameOverFont; }
    inline void setMenuFont(TTF_Font* tempFont){ m_MenuStartGameFont = tempFont; }
    inline void setGameOverFont(TTF_Font* tempFont){ m_GameOverFont = tempFont; }
    inline Mix_Chunk* getJumpSound(){return m_JumpSound; }
    inline Mix_Chunk* getLandSound(){return m_LandSound; }
    inline Mix_Chunk* getRunSound(){return m_RunSound; }
    inline Mix_Chunk* getDeathSound(){return m_DeathSound; }
    inline Mix_Chunk* getExplosionSound(){ return m_ExplosionSound; }

    inline Mix_Music* getBGMusic1(){return m_BGMusic1; }
    inline Mix_Music* getBGMusic2(){return m_BGMusic2; }
    inline Mix_Music* getIntroMusic(){return m_IntroMusic; }
    inline Mix_Music* getOutroMusic(){return m_OutroMusic; }

private:
    Engine(){}

    static Engine* s_Instance;
    bool  m_Running;
    int m_Score = 0;
    int m_HighScore = 0;
    std::string m_ScoreText;
    std::string m_HighScoreText;

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    GameMap* m_level0map;
    GameMap* m_level1map;
    GameMap* m_level2map;
    GameMap* m_level3map;
    GameMap* m_level4map;
    GameMap* m_levelspawnmap;
    //When render alaways update current map
    GameMap* m_currMap = nullptr;

    // An aray to store levelmap list
    std::vector <GameMap*> m_MapList;
    std::vector <LevelPart> m_LevelPartMapList;

    TTF_Font* m_MenuStartGameFont = nullptr;
    TTF_Font* m_GameOverFont = nullptr;
    TTF_Font* m_HighScoreFont = nullptr;

    Mix_Chunk* m_JumpSound = nullptr;
    Mix_Chunk* m_RunSound = nullptr;
    Mix_Chunk* m_LandSound = nullptr;
    Mix_Chunk* m_DeathSound = nullptr;
    Mix_Chunk* m_ExplosionSound = nullptr;
    
    Mix_Music* m_BGMusic1 = nullptr;
    Mix_Music* m_BGMusic2 = nullptr;
    Mix_Music* m_IntroMusic = nullptr;
    Mix_Music* m_OutroMusic = nullptr;

    bool PlayState;
    bool MenuState;
    bool GameOverState;
    bool ChangedState;
};

#endif //ENGINE_HPP