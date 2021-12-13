#include "SDL_Media.h"
#include "Game.h"
#include "Snake.h"


int main(int argc, char* args[])
{
    while (true)
    {
        Game game;

        game.run();

        if (!game.repeatGame)
        {
            break;
        }
    }


    return 0;
}