#include "SDL_Media.h"

SDL_Media::SDL_Media()
{
    if (!SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL coudl not initialize! SDL Error: %s", SDL_GetError());
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!\n");
        }

        window = SDL_CreateWindow("The Snake Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                }
            }
        }
    }
}


/* SDL_Media::~SDL_Media()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    window = nullptr;
    renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}
*/

void SDL_Media::clear()
{
    //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}


void SDL_Media::update()
{
    SDL_RenderPresent(renderer);
}