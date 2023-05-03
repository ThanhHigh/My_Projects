//Menu_cpp
#include "Menu.hpp"
#include "Play.hpp"
#include "Engine.hpp"
#include "KeyboardInput.hpp"
#include "Camera.hpp"

Menu* Menu::s_Instance = nullptr;

bool Menu::init()
{
    isMenu = true;
}

void Menu::render()
{
    
    if (isMenu) TextureManager::getInstance()->draw("Back_ground", 0, 0, 1920, 1080);
    else return;
}

void Menu::update()
{
    if (KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_B)) isMenu = false;
}

bool Menu::exit()
{
    std::cout << "exit menu!" << std::endl;
    //stuf
    return true;
}

//CallBack
void Menu::startGame()
{
    std::cout << "start game!\n";
}

void Menu::editor()
{
    std::cout << "editor mode\n";
}

void Menu::setting()
{
    std::cout << "options mode\n";

}

void Menu::quit()
{
    std::cout << "quit game\n";
}

