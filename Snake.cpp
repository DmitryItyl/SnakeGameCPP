#include "Snake.h"


Snake::Snake(int startX, int startY)
{
    headSourceFilePath = "/img/head.png";
    bodySourceFilePath = "/img/body.png";

    addSegment(startX, startY);
}


Snake::~Snake() 
{
    for (auto seg : body)
    {
        delete seg;
    }
}


void Snake::addSegment(int x, int y)
{
    if (!body.size())
    {
        Segment* seg = new Segment(x, y, EAST);
        body.push_back(seg);
        seg->textureSource = "img/head.png";
    }
    else
    {
        Segment* seg = new Segment(x, y, body.back()->direction);
        body.push_back(seg);
        seg->textureSource = "img/segment.png";
    }
}


void Snake::move()
{
    int dx = 0;
    int dy = 0;

    switch (body.front()->direction)
    {
    case NORTH:
        dx = 0;
        dy = -1;
        break;
    case WEST:
        dx = 1;
        dy = 0;
        break;
    case SOUTH:
        dx = 0;
        dy = 1;
        break;
    case EAST:
        dx = -1;
        dy = 0;
        break;
    default:
        break;
    }
    for (int i = body.size() - 1; i > 0; i--)
    {
        body[i]->x = body[i - 1]->x;
        body[i]->y = body[i - 1]->y;
        body[i]->direction = body[i - 1]->direction;
    }
    Segment* snakeHead = *(body.begin());
    snakeHead->x += dx;
    snakeHead->y += dy;
}


void Snake::setDirection(char dir)
{
    switch (body.front()->direction)
    {
    case NORTH:
        if (dir == SOUTH) return;
        if (body.size() > 1 && body[0]->y == body[1]->y) return;
        break;
    case WEST:
        if (dir == EAST) return;
        if (body.size() > 1 && body[0]->x == body[1]->x) return;
        break;
    case SOUTH:
        if (dir == NORTH) return;
        if (body.size() > 1 && body[0]->y == body[1]->y) return;
        break;
    case EAST:
        if (dir == WEST) return;
        if (body.size() > 1 && body[0]->x == body[1]->x) return;
        break;
    }

    body.front()->direction = dir;
}


void Snake::render(SDL_Renderer* renderer, int cellSize)
{
    //rendering the head
    SDL_Surface* tempSurface = IMG_Load(body.front()->textureSource.c_str());
    if (!tempSurface)
    {
        printf("Failed to load image %s! SDL Image Error: %s", body.front()->textureSource.c_str(), IMG_GetError());
    }

    SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_Rect objCell;
    objCell.w = objCell.h = cellSize;
    objCell.x = body.front()->x;
    objCell.y = body.front()->y;

    int angle = 0;
    switch (body.front()->direction)
    {
    case NORTH:
        angle = 0;
        break;
    case WEST:
        angle = 90;
        break;
    case SOUTH:
        angle = 180;
        break;
    case EAST:
        angle = 270;
        break;
    }

    SDL_RenderCopyEx(renderer, texture, NULL, &objCell, angle, NULL, SDL_FLIP_NONE);


    //rendering the rest
    for (int i = 1; i < body.size(); i++)
    { 
        SDL_Surface* tempSurface = IMG_Load(body[i]->textureSource.c_str());
        if (!tempSurface)
        {
            printf("Failed to load image %s! SDL Image Error: ", body[i]->textureSource.c_str(), IMG_GetError());
        }

        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        SDL_Rect objCell;
        objCell.w = objCell.h = cellSize;
        objCell.x = body[i]->x;
        objCell.y = body[i]->y;

        int angle = 0;
        switch (body[i]->direction)
        {
        case NORTH:
            angle = 0;
            break;
        case WEST:
            angle = 90;
            break;
        case SOUTH:
            angle = 180;
            break;
        case EAST:
            angle = 270;
            break;
        }

        SDL_RenderCopyEx(renderer, texture, NULL, &objCell, angle, NULL, SDL_FLIP_NONE);
    }
}