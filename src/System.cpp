#include "../include/System.h"
#include <SDL2/SDL.h>

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

        window = SDL_CreateWindow("Fruitwork", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
    }

    SDL_Renderer *System::get_renderer() const { return renderer; }

    System::~System()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    System sys;
} // fruitwork