#ifndef FRUITWORK_COMPONENT_H
#define FRUITWORK_COMPONENT_H

#include <SDL.h>

namespace fruitwork
{

    class Component {

    public:
        virtual ~Component();

        Component(const Component &) = delete; // no copy constructor

        const Component &operator=(const Component &) = delete; // no copy assignment

        virtual void onMouseDown(const SDL_Event &) {};

        virtual void onMouseUp(const SDL_Event &) {};

        virtual void onKeyDown(const SDL_Event &) {};

        virtual void onKeyUp(const SDL_Event &) {};

        virtual void draw() const = 0;

        const SDL_Rect &get_rect() const { return rect; }

    protected:
        Component(int x, int y, int w, int h);

    private:
        SDL_Rect rect;

    };

} // fruitwork

#endif //FRUITWORK_COMPONENT_H
