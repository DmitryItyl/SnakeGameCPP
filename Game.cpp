#include "Game.h"


Game::Game()
{
    framework = new SDL_Media();
    snake = new Snake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    snake->headTexture = framework->loadTexture(snake->headSourceFilePath);
    snake->bodyTexture = framework->loadTexture(snake->bodySourceFilePath);
    snake->turnTexture = framework->loadTexture(snake->turnSourceFilePath);
    snake->tailTexture = framework->loadTexture(snake->tailSourceFilePath);

    for (int i = 0; i < 5; i++)
    {
        snake->addSegment();
    }
}


Game::~Game()
{
    delete snake;
    delete framework;
}


void Game::run()
{
    bool running = true;

    const int frameDelay = 1000 / FRAMERATE;

    Uint32 frameTime;
    int frameElapsedTime;

    SDL_Event event;
    do
    {
        frameTime = SDL_GetTicks();
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
                    snake->setDirection(EAST);
                    break;
                case SDLK_DOWN:
                    snake->setDirection(SOUTH);
                    break;
                case SDLK_LEFT:
                    snake->setDirection(WEST);
                    break;
                case SDLK_RETURN:
                    snake->addSegment();
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

        frameElapsedTime = SDL_GetTicks() - frameTime;
        if (frameDelay > frameElapsedTime)
        {
            SDL_Delay(frameDelay - frameElapsedTime);
        }
    } while (running);
}


void Game::update()
{
    snake->move();
}


void Game::render()
{
    snake->render(framework->renderer);
}
