#include "Character.h"


std::vector<Character> segments;

Character::Character()
{
	mPosX = SCREEN_HEIGHT / 2;
	mPosY = SCREEN_WIDTH / 2;

	mVelX = 3;
	mVelY = 0;

	angle = 0;
}


void Character::setPosX(int x)
{
	mPosX = x;
}


void Character::setPosY(int y)
{
	mPosY = y;
}


int Character::getPosX()
{
	return mPosX;
}


int Character::getPosY()
{
	return mPosY;
}


void Character::setAngle(int newAngle)
{
	angle = newAngle;
}


int Character::getAngle()
{
	return angle;
}


void Character::setTexture()
{
	LTexture characterTexture;

	characterTexture.loadFromFile("segment.png");

	characterTexture.setWidth(CHARACTER_WIDTH);
	characterTexture.setHeight(CHARACTER_HEIGHT);

	characterTexture.render(mPosX, mPosY, angle);

	mTexture = characterTexture;
}


void Character::render()
{
	setTexture();
	for (Character segment : segments)
	{
		mTexture.render(mPosX, mPosY, angle);
	}
}


void Character::addSegment()
{
	if (!segments.size())
	{
		Character head;
		head.setTexture();

		head.setPosX(SCREEN_HEIGHT / 2);
		head.setPosX(SCREEN_WIDTH / 2);

		segments.push_back(head);
	}
	else
	{
		Character segment;
		//segment.setPosX();
	}
}


void Character::handleEvenet(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if ((angle == 0) || (angle == 180))
		{
			if (event.key.keysym.sym == SDLK_UP)
			{
				angle = 90;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				angle = 270;
			}
		}


		if (angle == 90)
		{
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				angle = 180;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				angle = 0;
			}
		}


		if (angle == 270)
		{
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				angle = 0;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				angle = 180;
			}
		}
	}
}