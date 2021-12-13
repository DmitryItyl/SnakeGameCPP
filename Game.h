#ifndef GAME_CORE_INCLUDED
#define GAME_CORE_INCLUDED

#include "Snake.h"
#include "SDL_Media.h"


struct Food
{
    int x;
    int y;
    SDL_Texture* texture;
    Food(int posX, int posY)
    {
        x = posX;
        y = posY;
    }
};



class Game
{

public:

    Game();
    ~Game();
    void run();
    void update();
    void render();
    void clean();
    void genNewFood();
    void handleEndGame();

    bool repeatGame = false;
    Food* food;
    std::string foodTextureSource;
private:

    bool snakeAlive;

    Snake* snake;
    SDL_Media* framework;

    int score = 0;
    int frameDelay = 1000;
};

#endif


