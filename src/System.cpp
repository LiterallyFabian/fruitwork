#include "System.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include "ExitScene.h"

namespace fruitwork
{
    System::System()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
            return;
        }
        else
        {
            SDL_Log("SDL initialized");
        }

        window = SDL_CreateWindow("fruitwork", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 900, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (TTF_Init() != 0)
        {
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_ttf: %s", TTF_GetError());
            return;
        }
        else
        {
            SDL_Log("SDL_ttf initialized");
        }

        font = TTF_OpenFont((constants::gResPath + "fonts/KGRedHands.ttf").c_str(), 36);

        if (font == nullptr)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load font: %s", TTF_GetError());
        else
            SDL_Log("Font loaded");

        if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) == -1)
        {
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_mixer: %s", Mix_GetError());
            return;
        }
        else
        {
            SDL_Log("SDL_mixer initialized");
        }
    }

    System::~System()
    {
        SDL_Log("Shutting down System");

        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Renderer *System::get_renderer() const { return renderer; }

    TTF_Font *System::get_font() const { return font; }

    void System::setNextScene(Scene *scene)
    {
        if (scene != ExitScene::get_instance())
            this->nextScene = scene;
    }

    void System::changeScene()
    {
        if (nextScene == nullptr)
            return;

        if (currentScene != nullptr)
            currentScene->exit(); // unload current scene

        nextScene->enter(); // load next scene

        currentScene = nextScene;
        nextScene = nullptr;
    }

    Scene *System::getCurrentScene() const
    {
        return currentScene;
    }

    System sys;
} // fruitwork