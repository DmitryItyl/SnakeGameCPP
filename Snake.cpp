#include "Snake.h"


Snake::Snake(int startX, int startY)
{
    headSourceFilePath = "img/head.png";
    bodySourceFilePath = "img/segment.png";
    addSegment();
}


Snake::~Snake() 
{
    for (auto seg : body)
    {
        delete seg;
    }
}


void Snake::addSegment()

{
    if (!body.size())
    {
        Segment* seg = new Segment(640 / 2, 480 / 2, WEST);
        body.push_back(seg);
        seg->textureSource = headSourceFilePath;
    }
    else
    {
        int posX, posY;
        
        switch (body.back()->direction)
        {
        case NORTH:
            posX = body.back()->x;
            posY = body.back()->y + CELL_SIZE;
            break;
        case WEST:
            posX = body.back()->x + CELL_SIZE;
            posY = body.back()->y;
            break;
        case SOUTH:
            posX = body.back()->x;
            posY = body.back()->y - CELL_SIZE;
            break;
        case EAST:
            posX = body.back()->x - CELL_SIZE;
            posY = body.back()->y;
            break;
        default:
            posX = 0;
            posY = 0;
            break;
        }

        Segment* seg = new Segment(posX, posY, body.back()->direction);
        body.push_back(seg);

        std::string textureSource = bodySourceFilePath;
        seg->textureSource = textureSource;
    }
}


void Snake::move()
{    
    for (int i = body.size() - 1; i > 0; i--)
    {
        body[i]->x = body[i - 1]->x;
        body[i]->y = body[i - 1]->y;
        body[i]->direction = body[i - 1]->direction; 
    }

    switch (body.front()->direction)
    {
    case NORTH:
        body.front()->y -= CELL_SIZE;
        if (body.front()->y < 0)
            body.front()->y += SCREEN_HEIGHT;
        break;
    case EAST:
        body.front()->x += CELL_SIZE;
        if (body.front()->x > SCREEN_WIDTH - CELL_SIZE)
            body.front()->x -= SCREEN_WIDTH;
        break;
    case SOUTH:
        body.front()->y += CELL_SIZE;
        if (body.front()->y > SCREEN_HEIGHT - CELL_SIZE)
            body.front()->y -= SCREEN_HEIGHT;
        break;
    case WEST:
        body.front()->x -= CELL_SIZE;
        if (body.front()->x < 0)
            body.front()->x += SCREEN_WIDTH;
        break;
    default:
        break;
    }
}


void Snake::setDirection(char dir)
{
    switch (body.front()->direction)
    {
    case NORTH:
        if (dir == SOUTH) return;
        break;
    case WEST:
        if (dir == EAST) return;
        break;
    case SOUTH:
        if (dir == NORTH) return;
        break;
    case EAST:
        if (dir == WEST) return;
        break;
    }

    body.front()->direction = dir;
}


void Snake::render(SDL_Renderer* renderer)
{
    for (auto segment:body)
    { 
        SDL_Surface* tempSurface = IMG_Load(segment->textureSource.c_str());
        if (!tempSurface)
        {
            printf("Failed to load image %s! SDL Image Error: ", segment->textureSource.c_str(), IMG_GetError());
        }
        else
        {
            SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
            SDL_FreeSurface(tempSurface);

            SDL_Rect objCell;
            objCell.w = objCell.h = CELL_SIZE;
            objCell.x = segment->x;
            objCell.y = segment->y;

            int angle = 0;
            switch (segment->direction)
            {
            case NORTH:
                angle = 0;
                break;
            case EAST:
                angle = 90;
                break;
            case SOUTH:
                angle = 180;
                break;
            case WEST:
                angle = 270;
                break;
            }

            SDL_RenderCopyEx(renderer, texture, NULL, &objCell, angle, NULL, SDL_FLIP_NONE);
        }        
    }
}
