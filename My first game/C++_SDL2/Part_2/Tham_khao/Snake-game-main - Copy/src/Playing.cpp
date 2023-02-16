///Playing [Source]
#include "Playing.h"

#include <ctime>
#include <random>

///Playing class
Playing::Playing()
{
    console = NULL;

    width = new int;
    height = new int;

    renderer = NULL;
    window = NULL;

    snake = NULL;
}

void Playing::init(SDL_Window* _window, SDL_Renderer* _renderer)
{
    console = new Console("Playing"); /* Set up console */

    window = _window; /* pass value/references */
    renderer = _renderer;
    SDL_GetWindowSize(window, width, height); 

    tileMap = new TileMap("res/map.dat", renderer, (*height)/PIXEL, (*width)/PIXEL); /* init tile map */
 
    if (tileMap->canRender())
        console->writeLine("Map init done!");

    snake = new Snake(0, 0, 32, 32); /* init snake */

    fruit = new Fruit(10, 8, 32, 32); /* init fruit */

    srand(time(NULL)); /* random for game */

    console->writeLine("Init done!");
}

void Playing::loop()
{
    if (fruit->isEaten()) /* Check xem quả đã bị ăn chưa */
    {
        fruit->genarate(); /* Nếu đúng -> Khởi tạo quả mới */
    }

    if ((snake->get_tile_x() == fruit->get_tile_x()) && (snake->get_tile_y() == fruit->get_tile_y()) && !fruit->isEaten()) /* nếu đầu rắn chạm vào tile của quả */
    {
        snake->eatFruit(); /* Đã ăn táo */
        fruit->setEaten();
    }

    fruit->update();  /* Update trước khi Render */

    snake->moving(); /* Trong hàm move rắn có update rắn */
}

void Playing::render()
{
    tileMap->render(); /* Render map trước tiên */

    // if (!fruit->isEaten()) /* Render quả khi quả chưa bị ăn */
    //     fruit->render();

    // snake->render(); /* render rắn cuối cùng */

    /* GỐC: Render Fruit trước khi Render Snake -> BUG: Rắn sẽ đè lên quả */

    snake->render();

    fruit->render();

    /* Render quả sau làm quả đè lên thân rắn */

}

void Playing::keyPressed(int key_sym)
{
    console->writeLine("Key pressed.");

    switch (key_sym)
    {
        case SDLK_UP:
            snake->setDir(DIRECTION::UP);
            break;
        case SDLK_DOWN:
            snake->setDir(DIRECTION::DOWN);
            break;
        case SDLK_LEFT:
            snake->setDir(DIRECTION::LEFT);
            break;
        case SDLK_RIGHT:
            snake->setDir(DIRECTION::RIGHT);
            break;
    }
}

void Playing::keyReleased(int key_sym)
{
    console->writeLine("Key released.");
}

void Playing::destroy()
{
    window = NULL;
    renderer = NULL;

    delete snake; /* snake là một con trỏ */
    snake = NULL;

    delete width; 
    width = NULL;
    delete height;
    height = NULL;

    console->writeLine("Destroyed Playing State!");

    delete console;
    console = NULL;
}
