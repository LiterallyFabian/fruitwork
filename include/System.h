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

        SDL_Renderer *get_renderer() const;

        TTF_Font *get_font() const;

        void setNextScene(Scene *scene);

        void changeScene();

        Scene *getCurrentScene() const;

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        TTF_Font *font;

        Scene *currentScene = nullptr;
        Scene *nextScene = nullptr;
    };

    extern System sys;

} // fruitwork

#endif //FRUITWORK_SYSTEM_H
