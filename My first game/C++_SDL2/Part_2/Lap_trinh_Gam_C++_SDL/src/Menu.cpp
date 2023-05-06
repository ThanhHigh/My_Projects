//Menu_cpp
#include "Menu.hpp"
#include "Play.hpp"
#include "Engine.hpp"
#include "KeyboardInput.hpp"
#include "Camera.hpp"

Menu* Menu::s_Instance = nullptr;

bool Menu::init()
{
    //Load texture
    isMenu = true;
}

void Menu::render()
{
    if (isMenu) TextureManager::getInstance()->drawBG("Menu", 0, 0, 1344, 768);


    TextureManager::getInstance()->drawText("MenuStartGame", "Start Game", 560, 350, colorMenuStart, Engine::GetInstance()->m_MenuStartGameFont);
    int w, h;
    w = TextureManager::getInstance()->m_getTextureWidth["MenuStartGame"];
    h = TextureManager::getInstance()->m_getTextureHeight["MenuStartGame"];
    StartGame = {560, 350, w, h};

    TextureManager::getInstance()->drawText("MenuQuitGame", "Quit Game", 570, 420, colorMenuQuit, Engine::GetInstance()->m_MenuStartGameFont);
    w = TextureManager::getInstance()->m_getTextureWidth["MenuQuitGame"];
    h = TextureManager::getInstance()->m_getTextureHeight["MenuQuitGame"];
    QuitGame = {570, 450, w, h};
    return;
}

void Menu::update()
{
    if (KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_B)) isMenu = false;

    if (KeyboardInput::getInstance()->mouseover(StartGame))
    {
        colorMenuStart = MOUSEOVER_COLOR;
        if (KeyboardInput::getInstance()->mouseclick())
        {
            isMenu = false;
        }
    }
    else
    {
        colorMenuStart = UNMOUSE_COLOR;
    }

    if (KeyboardInput::getInstance()->mouseover(QuitGame))
    {
        colorMenuQuit = MOUSEOVER_COLOR;
        if (KeyboardInput::getInstance()->mouseclick())
        {
            Engine::GetInstance()->quitGame();
        }
    }
    else
    {
        colorMenuQuit = UNMOUSE_COLOR;
    }
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

