
#include "GameOver.hpp"
#include "KeyboardInput.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"

GameOver* GameOver::s_Instance = nullptr;

void GameOver::init()
{
    m_GameOver = false;
    m_PlayAgain = false;
}

void GameOver::update()
{
    if ((m_GameOver == true) && (KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_O)))
    {
        m_GameOver = false;
        m_PlayAgain = true;
    }

    if (KeyboardInput::getInstance()->mouseover(PlayAgiain))
    {
        colorPlayAgain = MOUSEOVER_COLOUR;
        if (KeyboardInput::getInstance()->mouseclick())
        {
            m_GameOver = false;
            m_PlayAgain = true;
        }
    }
    else
    {
        colorPlayAgain = UNMOUSE_COLOUR;
    }

    if (KeyboardInput::getInstance()->mouseover(QuitGame))
    {
        colorQuitGame = MOUSEOVER_COLOUR;
        if (KeyboardInput::getInstance()->mouseclick())
        {
            Engine::GetInstance()->quitGame();
        }
    }
    else
    {
        colorQuitGame = UNMOUSE_COLOUR;
    }

}

void GameOver::updateDeath()
{
    m_GameOver = true;
}

void GameOver::render()
{
    if (m_GameOver) TextureManager::getInstance()->drawBG("GameOver", 0, 0, 1344, 768);

    TextureManager::getInstance()->drawText("GameOverPlayAgain", "Play Again", 570, 330, colorPlayAgain, Engine::GetInstance()->m_MenuStartGameFont );
    int w, h;
    w = TextureManager::getInstance()->m_getTextureWidth["GameOverPlayAgain"];
    h = TextureManager::getInstance()->m_getTextureHeight["GameOverPlayAgain"];
    PlayAgiain = {570, 330, w, h};

    TextureManager::getInstance()->drawText("GameOverQuitGame", "Quit Game", 570, 450, colorQuitGame, Engine::GetInstance()->m_MenuStartGameFont );
    w = TextureManager::getInstance()->m_getTextureWidth["GameOverQuitGame"];
    h = TextureManager::getInstance()->m_getTextureHeight["GameOverQuitGame"];
    QuitGame = {570, 450, w, h};
    return;
}

void GameOver::exit()
{

}