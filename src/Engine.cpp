#include "Engine.hpp"
#include "TextureManager.hpp"
#include "Warrior.hpp"
#include "KeyboardInput.hpp"
#include "Timer.hpp"
#include "MapParser.hpp"
#include "Camera.hpp"
#include "BackWall.hpp"
#include "Play.hpp"
#include "Menu.hpp"
#include "GameOver.hpp"
#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>

KeyboardInput* KeyboardInput::s_Instance = nullptr;
Engine* Engine::s_Instance = nullptr;
TextureManager* TextureManager::s_Instance = nullptr;
Warrior* player = nullptr;
Play* playState = nullptr;

bool Engine::initGame()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed to initilize SDL: %s ", SDL_GetError());
        return false;
    }

    //Window Flag
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("Run",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 window_flags);
    
    if (m_Window == nullptr) 
    {
        SDL_Log("Failed to create a Window: %s ", SDL_GetError());
        return false;
    }

    m_Renderer =  SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_Renderer == nullptr)
    {
        SDL_Log("Failed to create a Renderer: %s ", SDL_GetError());
        return false;
    }
    else
    {
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            std::cout << "SDL_image could not initialize! SDL_image Error" <<  IMG_GetError() << std::endl;
            return false;
        }
        //Initialize TTF loading
        if (TTF_Init() != 0)
        {
            std::cout << "SDL_ttf could not initialize! SDL_ttf Error:" << TTF_GetError() << std::endl;
            return false;
        }
        //Initialize SDL_mixer
		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error:" << Mix_GetError() << std::endl;
			return false;
		}
        
        //Load Media
        //Open the font
        m_MenuStartGameFont = TTF_OpenFont( "res/Elden_Ring.ttf", 50);
        if(m_MenuStartGameFont == nullptr)
        {
            std::cout << "Failed to load lazy font! SDL_ttf Error" << TTF_GetError() << std::endl;
        }
        m_GameOverFont = TTF_OpenFont("res/HK_font.ttf", 40);
        if (m_GameOverFont == nullptr)
        {
            std::cout << "Failed to load lazy font! SDL_ttf Error" << TTF_GetError() << std::endl;
        }
        m_HighScoreFont = TTF_OpenFont("res/Uni_Pixel.ttf", 30);
        if (m_HighScoreFont == nullptr)
        {
            std::cout << "Failed to load lazy font! SDL_ttf Error" << TTF_GetError() << std::endl;
        }

        //Open the Music&Sound
        m_IntroMusic = Mix_LoadMUS( "res/01 - Enter Hallownest.wav" );
	    if( m_IntroMusic == NULL )
	    {
            std::cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << std::endl;
	    }

        m_OutroMusic = Mix_LoadMUS( "res/26 - Hollow Knight.wav" );
	    if( m_OutroMusic == NULL )
	    {
            std::cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << std::endl;
	    }

        m_BGMusic1= Mix_LoadMUS( "res/06 - Hornet.wav" );
	    if( m_BGMusic1 == NULL )
	    {
            std::cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << std::endl;
	    }

        m_BGMusic2= Mix_LoadMUS( "res/18 - Broken Vessel.wav" );
	    if( m_BGMusic2 == NULL )
	    {
            std::cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << std::endl;
	    }

        m_DeathSound = Mix_LoadWAV("res/_death1.wav");
        if( m_DeathSound == NULL )
	    {
            std::cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << std::endl;
	    }

        m_RunSound = Mix_LoadWAV("res/_running.wav");
        if(m_RunSound == NULL )
	    {
            std::cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << std::endl;
	    }

        m_JumpSound = Mix_LoadWAV("res/_jump1.wav");
        if( m_JumpSound == NULL )
	    {
            std::cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << std::endl;
	    }

        m_ExplosionSound = Mix_LoadWAV("res/Explosion.wav");
        if(m_ExplosionSound == NULL )
	    {
            std::cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << std::endl;
	    }

        m_LandSound = Mix_LoadWAV("res/_land1.wav");
        if(  m_LandSound == NULL )
	    {
            std::cout << "Failed to load beat music! SDL_mixer Error:" << Mix_GetError() << std::endl;
	    }
        //Load Media

    }

    //Map
    if (MapParser::GetInstance()->load() == false) //Check error:
    {
        std::cout << "Failed to load map" << std::endl;
    }

    //If Map is oke
    m_level0map = MapParser::GetInstance()->GetMap("map1");
    m_MapList.push_back(m_level0map);
    m_level1map = MapParser::GetInstance()->GetMap("map2");
    m_MapList.push_back(m_level1map);
    m_level2map = MapParser::GetInstance()->GetMap("map3");
    m_MapList.push_back(m_level2map);
    m_level3map = MapParser::GetInstance()->GetMap("map4");
    m_MapList.push_back(m_level3map);
    m_level4map = MapParser::GetInstance()->GetMap("map5");
    m_MapList.push_back(m_level4map);
    m_levelspawnmap = MapParser::GetInstance()->GetMap("map_spawn");
    m_MapList.push_back(m_levelspawnmap);
    
    Engine::GetInstance()->createLevel();

    player = new Warrior (new Properties("Player", 400, 10, 120, 80));

    TextureManager::getInstance()->parseTextures("res/Texture.tml");

    //Take the target value of player
    Camera::getInstance()->setTarget(player->getOrigin());

    //BackWall
    if (!(BackWall::GetInstance()->createBackWall())) m_Running = false;

    //Menu&GameOVer
    Menu::GetInstance()->init();
    GameOver::GetInstance()->init();

    //State
    MenuState = true;
    PlayState = false;
    GameOverState = false;
    ChangedState = false;

    //Score
    m_Score = 0;
}
void Engine::updateGame()
{

    float deltaTime = Timer::GetInstance()->getDeltaTime();

    
    if (Menu::GetInstance()->isneedMenu() && ((PlayState == true) || (GameOverState == true)))
    {
        ChangedState = true;
    }

    if (Menu::GetInstance()->isneedMenu())
    {
        MenuState = true;
        PlayState = false;
        GameOverState = false;
    }
    else
    {
        MenuState = false;
        if (!(GameOver::GetInstance()->isOver()))
        {
            if (PlayState == false)
            {
                ChangedState = true;
            }
            GameOverState = false;
            PlayState = true;
        }
        else
        {
            if (GameOverState == false)
            {
                ChangedState = true;
            }
            GameOverState = true;
            PlayState = false;
        }
    }


    if (MenuState == true && PlayState == false && GameOverState == false)
    {
        Menu::GetInstance()->update();
    }
    if (MenuState == false && PlayState == true && GameOverState == false)
    {
        updateLevelMap();

        player->updateObject(deltaTime);

        //scoreupdate


        //scoreupdate

        Camera::getInstance()->update(deltaTime);

        BackWall::GetInstance()->udpate();

        if (player->Dead()) GameOver::GetInstance()->updateDeath();
    }
    if (MenuState == false && PlayState == false && GameOverState == true)
    {
        //GameOver
        GameOver::GetInstance()->update();

        //If play again, bring life to warrior, bring the game back
        if (GameOver::GetInstance()->wantPlayAgain())
        {
            player->setLive();
        
        //Play Again   
            Engine::GetInstance()->mapPlayAgain();
            player->playAgain();
            BackWall::GetInstance()->playAgian();
            m_Score = 0;
        //Play Againd
        }
    }

    //Mussic
    if (MenuState == true && PlayState == false && GameOverState == false)
    {
        if (Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(m_IntroMusic, -1);
        } 
    }
    if (MenuState == false && PlayState == true && GameOverState == false)
    {
        if (ChangedState)
        {
            if (Mix_PlayingMusic() != 0)
            {
                Mix_HaltMusic();
            }
            ChangedState = false;
        }
        if (Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(m_BGMusic1, -1);
        } 
    }
    if (MenuState == false && PlayState == false && GameOverState == true)
    {
        if (ChangedState)
        {
            if (Mix_PlayingMusic() != 0)
            {
                Mix_HaltMusic();
                Mix_HaltChannel(1);
            }
            ChangedState = false;
        }
        if (Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(m_OutroMusic, -1);
        } 
    }


    //Music
}
void Engine::renderGame()
{ 

    SDL_RenderClear(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer, 191, 148, 228, 120);

    if (MenuState == true && PlayState == false && GameOverState == false)
    {
        //Menu
        Menu::GetInstance()->render();
       
    }
    if (MenuState == false && PlayState == true && GameOverState == false)
    {

        Engine::GetInstance()->render_update_LevelPart();

        //Player update and render

        player->drawObject();

        //Score render
        if (m_Score < (player->getDistance() / 16)) m_Score = player->getDistance() / 16;
        std::stringstream ss;
        ss.str("");
        ss << m_Score;
        m_ScoreText = "";
        m_ScoreText = "Score: " + ss.str() + "m";
        SDL_Color whiteColor = {255, 255, 255, 255};
        SDL_Color yellowColor = {255, 255, 5, 255};

        std::ifstream readfile;
        readfile.open("res/HighScore.txt");
        if (readfile.fail())
        {
            //update highscore
            std::ofstream outfile;
            outfile.open("res/HighScore.txt");
            outfile.clear();
            outfile << m_HighScore;
            outfile.close();
            //update highscore
        }
        ss.str("");
        ss << m_HighScore;
        m_HighScoreText = "";
        m_HighScoreText = "Score: " + ss.str() + "m";

        TextureManager::getInstance()->drawText("Score", m_ScoreText, 1150, 20, whiteColor, m_HighScoreFont);
        //Score render

        //Wall Frame
        BackWall::GetInstance()->draw();
    }

    if (MenuState == false && PlayState == false && GameOverState == true)
    {
        GameOver::GetInstance()->render();
    }

    SDL_RenderPresent(m_Renderer);
    
}
void Engine::eventsGame()
{
    KeyboardInput::getInstance()->Listen();
}
void Engine::quitGame()
{
    m_Running = false;
}
void Engine::clearGame()
{
    TextureManager::getInstance()->cleanTexture();
    MapParser::GetInstance()->clean();
    SDL_DestroyRenderer(m_Renderer);
    m_Renderer = nullptr;
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

}


bool Engine::createLevel()
{
    for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
    {
            int random = rand() % (TOTAL_MAP - 1);
            if (i == 0) random = TOTAL_MAP - 1;
            GameMap* mapTemp = m_MapList.at(random);
            LevelPart level(i * LEVEL_WIDTH, 0, mapTemp);
            m_LevelPartMapList.push_back(level);
    }

    if (m_LevelPartMapList.size() < TOTAL_LEVEL_MAP)
    {
        std::cout << "Failed to create Level!" << std::endl;
    }
}

void Engine::render_update_LevelPart()
{
    //Debug check x viewbox
    int LevelPosX = m_LevelPartMapList.at(0).getX();
    int viewBoxX  = Camera::getInstance()->getViewBox().x;
    if ((LevelPosX - viewBoxX) <= (-LEVEL_WIDTH + 1)) 
    {
        int setXlevelMap = m_LevelPartMapList.at(m_LevelPartMapList.size() - 1).getX();
        setXlevelMap += LEVEL_WIDTH;
        int random = rand() % (TOTAL_MAP - 1);
        GameMap* mapTemp = m_MapList.at(random);
        m_LevelPartMapList.at(0).setLevelMap(mapTemp);
        m_LevelPartMapList.at(0).setLevelX(setXlevelMap);

        LevelPart level = m_LevelPartMapList.at(0);
        m_LevelPartMapList.erase(m_LevelPartMapList.begin());
        m_LevelPartMapList.push_back(level);
    }
    if (viewBoxX == 0)
    {
        for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
        {
            m_LevelPartMapList.at(i).renderLevelPart(i * LEVEL_WIDTH);       
        }
        // m_level0map->render();
    }
    else
    {
        for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
        {
            m_LevelPartMapList.at(i).renderLevelPart();
        }
    }
}

void Engine::updateLevelMap()
{
    for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
    {
            int LevelPosX = m_LevelPartMapList.at(i).getX();
            int ObjectX  = Camera::getInstance()->getTargetPos()->x;
            int viewBoxX = Camera::getInstance()->getPosition().X;
            if (ObjectX >= LevelPosX && ObjectX <= (LevelPosX + LEVEL_WIDTH - 1))
            {
                m_currMap = m_LevelPartMapList.at(i).getMapfromLevel();
                break;
            }
    }
}

void Engine::mapPlayAgain()
{
    for (int i = 0; i < m_LevelPartMapList.size(); i++)
    {
        int random = rand() % (TOTAL_MAP - 1);
        if (i == 0) random = TOTAL_MAP - 1;
        GameMap* mapTemp = m_MapList.at(random);
        m_LevelPartMapList.at(i).setLevelMap(mapTemp);
    }
}
