
#include "GameOver.hpp"
#include "KeyboardInput.hpp"
#include "TextureManager.hpp"

GameOver* GameOver::s_Instance = nullptr;

void GameOver::init()
{
    over = false;
}

void GameOver::update()
{

    if ((over == true) && (KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_O))) over = false;
}

void GameOver::updateDeath()
{
    over = true;
}

void GameOver::render()
{
    if (over) TextureManager::getInstance()->draw("Back_ground", 0, 0, 1920, 1080);
    else return;
}

void GameOver::exit()
{

}