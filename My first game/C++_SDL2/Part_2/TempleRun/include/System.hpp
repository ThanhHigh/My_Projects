//System [Header]
#ifndef System_hpp
#define System_hpp

//Include Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Console.hpp"
#include "Audio.hpp"
#include "Timer.hpp"
#include "Control.hpp"
#include "Graphic.hpp"

#include <set>
#include <string>

//System config
const std::string SYSTEM_CONFIG_PATH = "system.config";
const std::string SYSTEM_HIGHSCORE_PATH = "highscore.dat";

//Volume setting
const int VOLUME_SETTING_TOTAL = 11;
const int VOLUME_SETTING_VALUE[VOLUME_SETTING_TOTAL] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

//System struct
class System
{
private:
    
public:
    //Constructor
    System();

    //Destructor
    ~System();

    //Function:
    //init
    void init();
    void initAudio();
    void initTimer();
    void initControl();
    void initGraphic();

    //load

};

#endif //System_hpp