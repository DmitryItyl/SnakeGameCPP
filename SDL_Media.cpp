#include "SDL_Media.h"

SDL_Media::SDL_Media()
{
    if (!SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL coudl not initialize! SDL Error: %s", SDL_GetError());
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!\n");
        }

        window = SDL_CreateWindow("The Snake Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 79, 79, 79, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                }

                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                }
                else
                {
                    font = TTF_OpenFont("font/calibri.ttf", 32);
                    SDL_Color textColor = { 0, 0, 0, 0xFF };
                    if (font == nullptr)
                    {
                        printf("Failed to load calibri font! SDL_ttf Error: %s\n", TTF_GetError());
                    }
                }
            }
        }
    }
}


 SDL_Media::~SDL_Media()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    window = nullptr;
    renderer = nullptr;
    font = nullptr;

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}


void SDL_Media::clear()
{
    SDL_SetRenderDrawColor(renderer, 79, 79, 79, 0xFF);
    SDL_RenderClear(renderer);
}


void SDL_Media::update()
{
    SDL_RenderPresent(renderer);
}


SDL_Texture* SDL_Media::loadTexture(std::string source)
{
    SDL_Surface* tempSurface = IMG_Load(source.c_str());
    if (!tempSurface)
    {
        printf("Failed to load image %s! SDL Image Error: ", source.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        return texture;
    }
}


void SDL_Media::renderText(std::string text, int fontSize, int x, int y)
{
    TTF_Font* textFont = TTF_OpenFont("font/calibri.ttf", fontSize);


    SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface != NULL)
    {

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            SDL_Rect textFrame;
            textFrame.w = textSurface->w;
            textFrame.h = textSurface->h;
            textFrame.x = x - textSurface->w / 2;
            textFrame.y = y;
            SDL_RenderCopy(renderer, textTexture, NULL, &textFrame);
        }

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
        textFont = nullptr;
    }
    else
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
}


void SDL_Media::renderScore(int score)
{
    std::string scoreText = "Score: " + std::to_string(score);
    
    renderText(scoreText.c_str(), 32, 50, 0);
}


void SDL_Media::renderGameOverScreen(int score)
{
    //clear();

    std::string gameOverText = "Game over!";
    renderText(gameOverText.c_str(), 50, SCREEN_WIDTH / 2, 50);


    std::string endScoreText = "Your score: " + std::to_string(score);
    renderText(endScoreText.c_str(), 40, SCREEN_WIDTH / 2 + 4, 0.25 * SCREEN_HEIGHT);

    std::string promptText = "Press space to play again! Or press escape to quit.";
    renderText(promptText.c_str(), 50, SCREEN_WIDTH / 2, 0.75 * SCREEN_HEIGHT);
}