#include "Snake.h"


Snake::Snake(int startX, int startY)
{
    headSourceFilePath = "img/head.png";
    bodySourceFilePath = "img/segment.png";
    turnSourceFilePath = "img/turn.png";
    tailSourceFilePath = "img/tail.png";

    //addSegment();
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
        //seg->texture = headTexture;
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

        //seg->texture = bodyTexture;
    }
}


void Snake::move()
{
    for (int i = body.size() - 1; i > 0; i--)
    {
        body[i]->x = body[i - 1]->x;
        body[i]->y = body[i - 1]->y;
        body[i]->direction = body[i - 1]->direction;
        body[i]->isturn = body[i - 1]->isturn;
        body[i]->turnAngle = body[i - 1]->turnAngle;

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

    // make first body segment a turn
    if ((body.size()) > 2 && (body[1]->direction != body[2]->direction))
    {
        char turnAngle = body[1]->direction - body[2]->direction;
        if ((turnAngle == 3) || (turnAngle == -3))
            turnAngle = -turnAngle;

        body[1]->isturn = true;
        body[1]->turnAngle = body[2]->direction;
        if (turnAngle < 0)
            body[1]->turnAngle = body[1]->turnAngle == WEST ? NORTH : body[1]->turnAngle + 1;
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

    /*
       
    body.at(1)->isturn = true;

    char old_direction = body.front()->direction;

    if ((dir - old_direction) > 0)
    {
        body.at(1)->direction = old_direction;
    }
    else
    {
        switch (old_direction)
        {
        case NORTH:
            body.at(1)->direction = EAST;
        case EAST:
            body.at(1)->direction = SOUTH;
        case SOUTH:
            body.at(1)->direction = WEST;
        case WEST:
            body.at(1)->direction = NORTH;
        }
    }
    */
    body.front()->direction = dir;
}


void Snake::render(SDL_Renderer* renderer)
{
    for (auto segment:body)
    { 
            SDL_Rect objCell;
            objCell.w = objCell.h = CELL_SIZE;
            objCell.x = segment->x;
            objCell.y = segment->y;

            int angle = segment->direction * 90;
            SDL_Texture* texture = nullptr;
            if (segment == body.front())
            {
                texture = headTexture;
            }
            else if (segment == body.back())
            {
                texture = tailTexture;
            }
            else if (segment->isturn)
            {
                //segment->texture = turnTexture;
                texture = turnTexture;
                angle = segment->turnAngle * 90;
            }
            else
            {
                texture = bodyTexture;
            }

            SDL_RenderCopyEx(renderer, texture, NULL, &objCell, angle, NULL, SDL_FLIP_NONE);      
    }
}
