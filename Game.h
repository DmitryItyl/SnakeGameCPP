#ifndef GAME_CORE_INCLUDED
#define GAME_CORE_INCLUDED

#include "Snake.h"
#include "SDL_Media.h"

class Game
{

public:

    Game();
    ~Game();
    void run();
    void update();
    void render();
    void clean();

private:

    Snake* snake;
    SDL_Media* framework;

    const int cellSize = 40;
};

#endif


