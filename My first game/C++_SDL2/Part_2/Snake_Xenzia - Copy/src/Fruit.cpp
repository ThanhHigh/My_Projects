//Fruit [Source]
#include "Fruit.hpp"

//Include Headers
#include "Resources.hpp"

Fruit::Fruit(int x, int y, int w, int h)
{
    texture = Resources::getTexture(FRUIT_VAL);

    tile_x = x;
    tile_y = y;
    width = w;
    height = h;

    srcRect = {0, 0, width, height};

    isEatened = false;
}

Fruit::~Fruit()
{
}

void Fruit::generate()
{

}

void Fruit::load()
{

}

bool Fruit::isEaten()
{
    return isEatened;
}

void Fruit::render()
{

}

int Fruit::get_tile_x()
{
    return tile_x;
}
int Fruit::get_tile_y()
{
    return tile_y;
}


