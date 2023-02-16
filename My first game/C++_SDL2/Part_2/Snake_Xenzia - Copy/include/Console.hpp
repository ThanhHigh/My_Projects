//Console [Head]
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

//Include headers
#include <string>

enum ERROR_FLAGS
{
    SDL_ERROR = 0,
    IMG_ERROR,
    MIX_ERROR
};

class Console
{
public:
    Console(std::string name);
    void writeLine(std::string line);
    void error(std::string error, ERROR_FLAGS flag);

private:
    std::string main_name;
};


#endif //CONSOLE_HPP