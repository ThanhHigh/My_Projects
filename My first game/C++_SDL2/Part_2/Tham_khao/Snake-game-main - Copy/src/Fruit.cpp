///Fruit [Source]
#include "Fruit.h"

#include "Resources.h"
#include "TextureManager.h"

#include <random>

///Fruits
Fruit::Fruit(int x, int y, int w, int h)
{
    texture = Resources::getTexture(FRUIT_VAL);

    tile_x = x;
    tile_y = y;
    width = w;
    height = h;

    srcRect = {0, 0, width, height};

    eaten = false;
}

Fruit::~Fruit()
{

}

bool Fruit::isEaten()
{
    return eaten;
}

void Fruit::setEaten()
{
    eaten = true;
}

void Fruit::genarate()
{
    tile_x = rand() % 20; /* Tạo ra quả táo ở tọa độ bất kỳ trong map */
    tile_y = rand() % 15;

    eaten = false;

    /* BUG: Có thể quả tạo rand trùng dưới thân rắn */
}

void Fruit::update()
{
    screen_x = tile_x*PIXEL; // Lấy giá trị Screen x, y của quả táo
    screen_y = tile_y*PIXEL;
}

void Fruit::render()
{
    destRect = {screen_x, screen_y, width, height}; /* Set up DesRect cần render: tọa độ screen, độ rộng và cao theo init ban đầu là 32*/
    TextureManager::draw(texture, srcRect, destRect); /* texture ở đây là fruit -> Đã hiểu tại sao hàm getTexture lại lấy return SDL_Texture */
}

int Fruit::get_tile_x()
{
    return tile_x;
}

int Fruit::get_tile_y()
{
    return tile_y;
}
