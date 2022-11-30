#include <SDL.h>
#include <iostream>
#include "Session.h"
#include "System.h"
#include "Constants.h"
#include <algorithm>

namespace fruitwork
{
    void Session::add_component(Component *component)
    {
        components.push_back(component);
        component->start();
    }

    void Session::run(Scene *startScene)
    {
        bool running = true;

        sys.setNextScene(startScene);
        sys.changeScene();

        const int tickInterval = 1000 / constants::gFps;

        while (running)
        {
            Uint32 nextTick = SDL_GetTicks() + tickInterval;

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

                        for (auto component: sys.getCurrentScene()->get_components())
                            component->onMouseDown(event);

                        break;
                    }

                    case SDL_MOUSEBUTTONUP:
                    {
                        for (auto component: components)
                            component->onMouseUp(event);

                        for (auto component: sys.getCurrentScene()->get_components())
                            component->onMouseUp(event);

                        break;
                    }

                    case SDL_TEXTINPUT:
                    {
                        for (auto component: components)
                            component->onTextInput(event);

                        for (auto component: sys.getCurrentScene()->get_components())
                            component->onTextInput(event);

                        break;
                    }

                    case SDL_TEXTEDITING:
                    {
                        for (auto component: components)
                            component->onTextEditing(event);

                        for (auto component: sys.getCurrentScene()->get_components())
                            component->onTextEditing(event);

                        break;
                    }

                    case SDL_KEYDOWN:
                    {
                        for (auto component: components)
                            component->onKeyDown(event);

                        for (auto component: sys.getCurrentScene()->get_components())
                            component->onKeyDown(event);

                        break;
                    }

                    case SDL_KEYUP:
                    {
                        for (auto component: components)
                            component->onKeyUp(event);

                        for (auto component: sys.getCurrentScene()->get_components())
                            component->onKeyUp(event);

                        break;
                    }

                } // switch

                sys.getCurrentScene()->handleEvent(event);
            } // while event

            // update session components
            for (Component *component: components)
                component->update();

            // update scene
            sys.getCurrentScene()->update();
            for (Component *component: sys.getCurrentScene()->get_components())
                component->update();

            sys.changeScene();

            SDL_SetRenderDrawColor(fruitwork::sys.get_renderer(), 255, 255, 255, 255);
            SDL_RenderClear(fruitwork::sys.get_renderer());

            // draw scene
            sys.getCurrentScene()->draw();
            for (Component *component: sys.getCurrentScene()->get_components())
                component->draw();

            // draw session components
            for (Component *component: components)
                component->draw();

            // delete components marked for deletion
            sys.getCurrentScene()->deleteComponents();

            SDL_RenderPresent(fruitwork::sys.get_renderer());

            int delay = nextTick - SDL_GetTicks();
            if (delay > 0)
            {
                SDL_Delay(delay);
            }

        } // while running

        std::cout << "Session ended" << std::endl;
    }

    Session::~Session()
    {
        std::cout << "Session destructor" << std::endl;
        for (auto component: components)
            delete component;
    }

    void Session::remove_component(Component *component)
    {
        components.erase(std::remove(components.begin(), components.end(), component), components.end());
    }
} // fruitwork