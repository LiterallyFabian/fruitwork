#ifndef FRUITWORK_SYSTEM_H
#define FRUITWORK_SYSTEM_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Scene.h"

namespace fruitwork
{

    class System {
    public:
        System();

        ~System();

        SDL_Renderer *getRenderer() const;

        TTF_Font *getFont() const;

        void setNextScene(Scene *scene);

        void changeScene();

        Scene *getCurrentScene() const;

        SDL_Cursor *getCursorDefault() const { return cursorDefault; }

        SDL_Cursor *getCursorPointer() const { return cursorPointer; }

        SDL_Cursor *getCursorText() const { return cursorText; }

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        TTF_Font *font;

        Scene *currentScene = nullptr;
        Scene *nextScene = nullptr;

        SDL_Cursor *cursorDefault;
        SDL_Cursor *cursorPointer;
        SDL_Cursor *cursorText;
    };

    extern System sys;

} // fruitwork

#endif //FRUITWORK_SYSTEM_H
