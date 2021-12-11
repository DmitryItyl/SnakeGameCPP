#include "Game.h"


Game::Game(SDL_Media uframework)
{
    framework = &uframework;
    snake = new Snake(framework->SCREEN_WIDTH / 2, framework->SCREEN_HEIGHT / 2);
}


Game::~Game()
{
    delete snake;
}


void Game::run()
{
    bool running = true;
    SDL_Event event;
    do
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    snake->setDirection(NORTH);
                    break;
                case SDLK_RIGHT:
                    snake->setDirection(WEST);
                    break;
                case SDLK_DOWN:
                    snake->setDirection(SOUTH);
                    break;
                case SDLK_LEFT:
                    snake->setDirection(EAST);
                    break;
                case SDLK_RETURN:
                    snake->addSegment(snake->body.back()->x, snake->body.back()->y);
                    break;
                default:
                    break;
                }
            }
            else if (event.type == SDL_QUIT) running = false;
        }
        update();
        framework->clear();
        render();
        framework->update();
    } while (running);
}


void Game::update()
{
    snake->move();
}


void Game::render()
{
    snake->render(framework->renderer, cellSize);
}
