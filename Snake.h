#ifndef SNAKE_INCLUDE
#define SNAKE_INCLUDE

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cstdlib>
#include <string>


#include "SDL_Media.h"


static const char NORTH = 0;
static const char WEST = 1;
static const char SOUTH = 2;
static const char EAST = 3;


struct Segment
{
    int x;
    int y;
    std::string textureSource;
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
    void addSegment(int x, int y);
    void move();
    void setDirection(char dir);
    void render(SDL_Renderer* renderer, int cellSize);

    std::vector<Segment*> body;

private:
    std::string headSourceFilePath;
    std::string bodySourceFilePath;
};

#endif
