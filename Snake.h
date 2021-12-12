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
static const char EAST = 1;
static const char SOUTH = 2;
static const char WEST = 3;


struct Segment
{
    int x;
    int y;
    //SDL_Texture* texture;
    char direction;

    bool isturn = false;
    char turnAngle = 0;
    //char turnDirection = 0;

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
    void move();
    void setDirection(char dir);
    void render(SDL_Renderer* renderer);
    bool checkFood(int x, int y);
    bool detectCollision(int x, int y, bool checkHead);

    std::vector<Segment*> body;

    std::string headSourceFilePath;
    std::string bodySourceFilePath;
    std::string turnSourceFilePath;
    std::string tailSourceFilePath;
    std::string foodSourceFilePath;
    
    SDL_Texture* headTexture = nullptr;
    SDL_Texture* bodyTexture = nullptr;
    SDL_Texture* turnTexture = nullptr;
    SDL_Texture* tailTexture = nullptr;
    SDL_Texture* foodTexture = nullptr;

private:
    void addSegment();
    char newDirection = 1;
};

#endif