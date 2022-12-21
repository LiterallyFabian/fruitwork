#include "System.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
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

        window = SDL_CreateWindow("fruitwork", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, constants::gScreenWidth, constants::gScreenHeight, SDL_WINDOW_SHOWN);
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

        font = TTF_OpenFont(constants::gDefaultFontPath.c_str(), 24);

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
            Mix_AllocateChannels(16); // very fast beatmaps will need more channels
            SDL_Log("SDL_mixer initialized");
        }

        // set cursor
        SDL_Surface *cursorSurface = IMG_Load((constants::gResPath + "cursors/normal.cur").c_str());
        cursorDefault = SDL_CreateColorCursor(cursorSurface, 0, 0);

        SDL_Surface *pointerSurface = IMG_Load((constants::gResPath + "cursors/link.cur").c_str());
        cursorPointer = SDL_CreateColorCursor(pointerSurface, 0, 0);

        SDL_Surface *textSurface = IMG_Load((constants::gResPath + "cursors/text.cur").c_str());
        cursorText = SDL_CreateColorCursor(textSurface, 0, 0);

        SDL_SetCursor(cursorDefault);
        SDL_FreeSurface(cursorSurface);
        SDL_FreeSurface(pointerSurface);
        SDL_FreeSurface(textSurface);
    }

    System::~System()
    {
        SDL_Log("Shutting down System");

        SDL_FreeCursor(cursorDefault);
        SDL_FreeCursor(cursorPointer);
        SDL_FreeCursor(cursorText);

        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void System::setNextScene(Scene *scene)
    {
        if (scene != ExitScene::getInstance())
            this->nextScene = scene;
    }

    void System::changeScene()
    {
        if (nextScene == nullptr)
            return;

        SDL_Log("Changing scene...");

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