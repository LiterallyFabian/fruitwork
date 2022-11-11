#include <SDL.h>
#include <iostream>
#include "Session.h"
#include "System.h"

namespace fruitwork
{
    void Session::add_component(Component *component)
    {
        components.push_back(component);
    }

    void Session::run()
    {
        bool running = true;

        while (running)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                    {
                        running = false;
                        break;
                    }

                    case SDL_MOUSEBUTTONDOWN:
                    {
                        for (auto component: components)
                            component->onMouseDown(event);
                        break;
                    }

                    case SDL_MOUSEBUTTONUP:
                    {
                        for (auto component: components)
                            component->onMouseUp(event);
                        break;
                    }

                    case SDL_KEYDOWN:
                    {
                        for (auto component: components)
                            component->onKeyDown(event);
                        break;
                    }

                    case SDL_KEYUP:
                    {
                        for (auto component: components)
                            component->onKeyUp(event);
                        break;
                    }

                } // switch
            } // while event

            SDL_SetRenderDrawColor(fruitwork::sys.get_renderer(), 0, 255, 255, 255);
            SDL_RenderClear(fruitwork::sys.get_renderer());

            for (Component *component: components)
                component->draw();

            SDL_RenderPresent(fruitwork::sys.get_renderer());

        } // while running
    }

    Session::~Session()
    {
        for (auto component: components)
            delete component;

    }
} // fruitwork