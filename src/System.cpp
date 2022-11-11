#include "System.h"
#include <SDL.h>
#include "Constants.h"

namespace fruitwork
{
    System::System()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            return;
        }
        else
        {
            SDL_Log("SDL initialized");
        }

        window = SDL_CreateWindow("fruitwork", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (TTF_Init() != 0)
        {
            SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
            return;
        }
        else
        {
            SDL_Log("SDL_ttf initialized");
        }

        //font = TTF_OpenFont("D:/Skrivbord/Saker/fonts/KGRedHands.ttf", 36);
        font = TTF_OpenFont((constants::gResPath + "fonts/KGRedHands.ttf").c_str(), 36);
    }

    System::~System()
    {
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Renderer *System::get_renderer() const { return renderer; }

    TTF_Font *System::get_font() const { return font; }

    System sys;
} // fruitwork