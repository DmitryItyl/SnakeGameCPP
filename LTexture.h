#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>



class LTexture
{
public:
	LTexture();
	~LTexture();


	bool loadFromFile(SDL_Renderer* renderer, std::string path);
	void render(SDL_Renderer* renderer, int x, int y, double angle);
	void free();


	int getWidth();
	int getHeight();


	void setWidth(int newWidth);
	void setHeight(int newHeight);


private:
	SDL_Texture* mTexture;


	int mWidth;
	int mHeight;
};