#ifndef FRUITWORK_SYSTEM_H
#define FRUITWORK_SYSTEM_H

#include <SDL.h>

namespace fruitwork
{

    class System {
    public:
        System();

        ~System();

        SDL_Renderer *get_renderer() const;

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
    };

    extern System sys;

} // fruitwork

#endif //FRUITWORK_SYSTEM_H
