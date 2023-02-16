//Console [Header]
#ifndef Console_hpp
#define Console_hpp

//Include Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <string>

enum ERROR_FLAGS
{
    SDL_ERROR = 0,
    IMG_ERROR,
    MIX_ERROR,
    ERROR_FLAGS_TOTAL

};

class Console
{
    public:
        //Constructor
        Console(std::string name);

        //Destructor
        ~Console();

        //writeline
        void writeLine(std::string line);

        //logError:
        void logError(std::string error, ERROR_FLAGS flag);
    private:
        //main part name
        std::string main_name;
};

#endif //Console_hpp