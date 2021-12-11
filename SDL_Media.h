#ifndef SDLM_INCLUDE
#define SDLM_INCLUDE


#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <string>
#include <vector>


#include "Snake.h"
#include "GlobalConstants.h"


class SDL_Media
{

public:
    SDL_Media();
    ~SDL_Media();
    
    void clear();
    void update();

    void setPlayBoard(int cellSize);

    SDL_Texture* loadTexture(std::string source);

    SDL_Renderer* renderer = nullptr;

private:
    SDL_Window* window = nullptr;
};

#endif

