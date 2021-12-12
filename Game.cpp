#include <cstdlib>

#include "Game.h"

Game::Game()
{
    framework = new SDL_Media();
    snake = new Snake(CELL_SIZE * 10, CELL_SIZE * 8);

    snake->headTexture = framework->loadTexture(snake->headSourceFilePath);
    snake->bodyTexture = framework->loadTexture(snake->bodySourceFilePath);
    snake->turnTexture = framework->loadTexture(snake->turnSourceFilePath);
    snake->tailTexture = framework->loadTexture(snake->tailSourceFilePath);

    srand(SDL_GetTicks());

    food = new Food(0, 0);
    genNewFood();
    
    snakeAlive = true;

    foodTextureSource = "img/food.png";
    food->texture = framework->loadTexture(foodTextureSource);
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
                default:
                    break;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                return;
            }
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
        
    } while (snakeAlive);
}


void Game::update()
{
    snake->move();

    if (snake->checkFood(food->x, food->y))
    {
        score++;
        genNewFood();
    }

    Segment* head = snake->body.front();
    if (snake->detectCollision(head->x, head->y, false))
    {
        snakeAlive = false;
        handleEndGame();
    }
}


void Game::render()
{
    snake->render(framework->renderer);


    SDL_Rect foodCell;

    foodCell.x = food->x;
    foodCell.y = food->y;
    foodCell.w = foodCell.h = CELL_SIZE;

    SDL_RenderCopy(framework->renderer, food->texture, NULL, &foodCell);

    framework->renderScore(score);
}


void Game::genNewFood()
{
    do
    {
        food->x = rand() % GRID_W * CELL_SIZE;
        food->y = rand() % GRID_H * CELL_SIZE;
    } while (snake->detectCollision(food->x, food->y, true));

}


void Game::handleEndGame()
{
    framework->renderGameOverScreen(score);
    framework->update();

    SDL_Event userInput;
    while (true)
    {
        while (SDL_PollEvent(&userInput))
        {
            if (userInput.type == SDL_KEYDOWN)
            {
                if (userInput.key.keysym.sym == SDLK_SPACE)
                {
                    repeatGame = true;
                    return;
                }
                else if (userInput.key.keysym.sym == SDLK_ESCAPE)
                {
                    repeatGame = false;
                    return;
                }
            }
        }
    }
}