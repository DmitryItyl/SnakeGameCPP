#ifndef SDLM_INCLUDE
#define SDLM_INCLUDE


#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <string>
#include <vector>


#include "Snake.h"


class SDL_Media
{

public:
    SDL_Media();
    //~SDL_Media();
    
    void clear();
    void update();

    void setPlayBoard(int cellSize);

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Renderer* renderer = nullptr;

private:
    SDL_Window* window = nullptr;
};

#endif

