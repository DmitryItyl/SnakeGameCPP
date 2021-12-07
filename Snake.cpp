#include "Snake.h"


Snake::Snake(int startX, int startY, char dir)
{
    direction = dir;
    headTexture = loadTexture();
}


~Snake();
void addSegment(int x, int y);
void move();


SDL_Texture* Snake::loadTexture(const char* filename)
{
    //placeholder surface
    SDL_Surface* tSurface = IMG_Load(filename);
    if (!tSurface)
    {
        printf("Failed to load image %s! SDL_image error: %s", filename, IMG_GetError());
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface();
}


void setDirection(char dir);