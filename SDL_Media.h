#ifndef SDLM_INCLUDE
#define SDLM_INCLUDE


#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SDL_Media
{

public:
    SDL_Media();
    ~SDL_Media();
    void renderOnScreen(std::string filePath, std::string directionKey, std::string segmentTypeKey);

private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
};

#endif

