#pragma once
#include <SDL.h>
#include <vector>

#include "LTexture.h"

class Character
{
public:
    
    static const int CHARACTER_WIDTH = 50;
    static const int CHARACTER_HEIGHT = 50;


    Character();


    static const int CHARACTER_VEL = 3;
    

    void setPosX(int x);
    void setPosY(int y);


    int getPosX();
    int getPosY();

    void setAngle(int angle);
    int getAngle();


    void setTexture();
    void handleEvenet(SDL_Event& event);
    void addSegment();
    void render();
    void move();


private:
    
    int mPosX, mPosY;
    int mVelX, mVelY;
    int angle = 0;

    LTexture mTexture;

};