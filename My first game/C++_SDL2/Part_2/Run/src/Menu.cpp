//Menu_cpp
#include "Menu.hpp"
#include "Play.hpp"
#include "Engine.hpp"
#include "KeyboardInput.hpp"

Menu::Menu(){}

bool Menu::init()
{
    m_Ctxt = Engine::GetInstance()->getRenderer();
    std::cout << "Menu initialized! " << std::endl;
    return true;
}

void Menu::render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 130, 40, 50, 200);
    SDL_RenderClear(m_Ctxt);
    //stuf
    SDL_RenderPresent(m_Ctxt);
}

void Menu::update(){}

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

