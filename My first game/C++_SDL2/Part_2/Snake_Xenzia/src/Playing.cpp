//Playing [Sources]
#include "Playing.hpp"

//Include Header
#include <ctime>
#include <random>

//class Playing
Playing::Playing()
{
    console = NULL;
    renderer = NULL;
    window = NULL;

    width = new int;
    height = new int;

    snake = NULL;
}

void Playing::init(SDL_Window* _window, SDL_Renderer* _renderer)
{
    console = new Console("Playing");

    window = _window;
    renderer = _renderer;

    SDL_GetWindowSize(window, width, height);

    tilemap = new TileMap("res/map.dat", renderer, (*width)/PIXEL, (*height)/PIXEL);

    if (tilemap->canRender())
        console->writeLine("Map init done");

    snake = new Snake(0, 0, 32, 32); //set 32 cz snake resources can change and update later

    fruit = new Fruit(3, 3, 32, 32);

    srand(time(NULL));

    console->writeLine("Initilized!");
}

void Playing::loop()
{
    //Check gamelogic
    if (fruit->isEaten()) 
        fruit->generate();


    if ((snake->get_tile_x() == fruit->get_tile_x() && snake->get_tile_y() == fruit->get_tile_y()) && (fruit->isEaten() == false))
    {
        snake->eaten();
        fruit->isEaten();
    }

    fruit->load();

    //Update snake and Moving snake
}

void Playing::keyPress(int key_sym)
{

}

void Playing::keyRelease(int key_sym)
{

}

void Playing::render()
{
    tilemap->render();

    snake->render();

    fruit->render();
}

void Playing::destroy()
{
    window = NULL;
    renderer = NULL;

    delete snake;
    snake = NULL;
    delete width;
    width = NULL;
    delete height;
    height = NULL;

    console->writeLine("Destroying Playing State!");

    delete console;
    console = NULL;
}