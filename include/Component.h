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

        virtual void onTextInput(const SDL_Event &) {};

        virtual void onTextEditing(const SDL_Event &) {};

        virtual void draw() const = 0;

        /**
         * Update is called every frame.
         */
        virtual void update() {};

        /**
         * Start is called when the component is added to a session.
         */
        virtual void start() {};

        const SDL_Rect &get_rect() const { return rect; }

        void set_rect(const SDL_Rect &rect) { this->rect = rect; }

        int width() const { return rect.w; }

        int height() const { return rect.h; }

    protected:
        Component(int x, int y, int w, int h);

    private:
        SDL_Rect rect;

    };

} // fruitwork

#endif //FRUITWORK_COMPONENT_H
