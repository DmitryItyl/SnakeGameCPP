#ifndef SNAKE_INCLUDE
#define SNAKE_INCLUDE

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cstdlib>
#include <string>


struct Segment
{
    int x;
    int y;
    Segment(int posX, int posY)
    {
        x = posX;
        y = posY;
    }
};


class Snake
{

public:
    Snake(int startX, int startY, char dir);
    ~Snake();
    void addSegment(int x, int y);
    void move();
    void setDirection(char dir);

    static const char NORTH = 0;
    static const char WEST  = 1;
    static const char SOUTH = 2;
    static const char EAST  = 3;

private:
    std::vector<Segment*> body;
    char direction;
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
};

#endif
