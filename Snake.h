#ifndef SNAKE_INCLUDE
#define SNAKE_INCLUDE

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cstdlib>
#include <string>


#include "SDL_Media.h"
#include "GlobalConstants.h"

static const char NORTH = 0;
static const char WEST = 1;
static const char SOUTH = 2;
static const char EAST = 3;


struct Segment
{
    int x;
    int y;
    SDL_Texture* texture;
    char direction;
    Segment(int posX, int posY, char _direction)
    {
        x = posX;
        y = posY;
        direction = _direction;
    }
};


class Snake
{

public:
    Snake(int startX, int startY);
    ~Snake();
    void addSegment();
    void move();
    void setDirection(char dir);
    void render(SDL_Renderer* renderer);

    std::vector<Segment*> body;
    std::string headSourceFilePath;
    std::string bodySourceFilePath;
    
    SDL_Texture* headTexture = nullptr;
    SDL_Texture* bodyTexture = nullptr;
};

#endif