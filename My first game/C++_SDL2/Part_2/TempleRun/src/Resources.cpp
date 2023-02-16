//Resources [Source]
#include "Resources.hpp"

//Include Header
#include "Texture.hpp"

Resources::Resources()
{
    console = new Console("Resources");

    texture = NULL;

    background = NULL;

    return;
}

Resources::~Resources()
{
    texture = NULL;

    delete console;
    console = NULL;

    return;
}

void Resources::init(Texture* _texture)
{
    texture = _texture;

    load();

    create();

    console->writeLine("Initlized Resources.");

    return;
}

void Resources::load()
{
    console->writeLine("Loading Resources:. . .");

    background = texture->load("res/dark_knight.png");

    return;
}

void Resources::create()
{
    return;
}

void Resources::free()
{
    return;
}

void Resources::close()
{
    return;
}