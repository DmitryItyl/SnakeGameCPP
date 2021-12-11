#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>


#include "SDL_Media.h"
#include "Game.h"
#include "Snake.h"


int main(int argc, char* args[])
{
    //SDL_Media framework;

    Game game;

    game.run();

    return 0;
}