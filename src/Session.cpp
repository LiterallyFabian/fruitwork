#include <SDL.h>
#include <iostream>
#include "Session.h"
#include "System.h"
#include "Constants.h"
#include <algorithm>

namespace fruitwork
{
    void Session::addComponent(Component *component)
    {
        components.push_back(component);

        if (component->getPhysicsBody() != nullptr)
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Session components will not have their physics bodies updated. Use Scene components instead.");

        std::stable_sort(components.begin(), components.end(), [](Component *a, Component *b)
        {
            return a->zIndex() < b->zIndex();
        });

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
            float elapsedTime = 0;
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

                        for (auto component: sys.getCurrentScene()->getComponents())
                            component->onMouseDown(event);

                        break;
                    }

                    case SDL_MOUSEBUTTONUP:
                    {
                        for (auto component: components)
                            component->onMouseUp(event);

                        for (auto component: sys.getCurrentScene()->getComponents())
                            component->onMouseUp(event);

                        break;
                    }

                    case SDL_TEXTINPUT:
                    {
                        for (auto component: components)
                            component->onTextInput(event);

                        for (auto component: sys.getCurrentScene()->getComponents())
                            component->onTextInput(event);

                        break;
                    }

                    case SDL_TEXTEDITING:
                    {
                        for (auto component: components)
                            component->onTextEditing(event);

                        for (auto component: sys.getCurrentScene()->getComponents())
                            component->onTextEditing(event);

                        break;
                    }

                    case SDL_KEYDOWN:
                    {
                        // keyboard event handler
                        auto it = keyboardEventHandlers.find(event.key.keysym.sym);
                        if (it != keyboardEventHandlers.end())
                            it->second();

                        for (auto component: components)
                            component->onKeyDown(event);

                        for (auto component: sys.getCurrentScene()->getComponents())
                            component->onKeyDown(event);

                        break;
                    }

                    case SDL_KEYUP:
                    {
                        for (auto component: components)
                            component->onKeyUp(event);

                        for (auto component: sys.getCurrentScene()->getComponents())
                            component->onKeyUp(event);

                        break;
                    }

                } // switch

                sys.getCurrentScene()->handleEvent(event);
            } // while event

            elapsedTime = (float) (nextTick - SDL_GetTicks()) / 1000;

            // update session components
            for (Component *component: components)
                component->update();

            // update scene
            sys.getCurrentScene()->update();
            for (int i = 0; i < sys.getCurrentScene()->getComponents().size(); i++)
            {
                Component *component = sys.getCurrentScene()->getComponents()[i];
                component->update();
                component->update(elapsedTime);

                // go through all components and check for physics collisions
                // todo: optimize this, its worst case is O(n^2) (assuming all comps have bodies). maybe store a list of components with physics bodies?
                PhysicsBody *bodyA = component->getPhysicsBody();
                if (bodyA != nullptr && bodyA->getObjCollision())
                {
                    for (int j = 0; j < sys.getCurrentScene()->getComponents().size(); j++)
                    {
                        Component *other = sys.getCurrentScene()->getComponents()[j];
                        PhysicsBody *bodyB = other->getPhysicsBody();

                        if (i != j && bodyB != nullptr && bodyB->getObjCollision() && bodyA->isColliding(bodyB))
                        {
                            bodyA->resolveCollision(bodyB);
                        }
                    }
                }
            }

            auto oldScene = sys.getCurrentScene();
            sys.changeScene();

            SDL_SetRenderDrawColor(fruitwork::sys.getRenderer(), 255, 255, 255, 255);
            SDL_RenderClear(fruitwork::sys.getRenderer());

            // draw scene
            sys.getCurrentScene()->draw();
            for (Component *component: sys.getCurrentScene()->getComponents())
                component->draw();

            // draw session components
            for (Component *component: components)
                component->draw();

            // delete components marked for deletion
            oldScene->deleteComponents();
            this->deleteComponents();

            SDL_RenderPresent(fruitwork::sys.getRenderer());

            int delay = nextTick - SDL_GetTicks();
            if (delay > 0)
            {
                SDL_Delay(delay);
            }

        } // while running

        std::cout << "Session ended" <<
                  std::endl;
    }

    Session::~Session()
    {
        std::cout << "Session destructor" << std::endl;

        for (auto component: components)
            delete component;

        // delete scene comps
        for (auto component: sys.getCurrentScene()->getComponents())
            delete component;
    }

    void Session::removeComponent(Component *component, bool destroy)
    {
        componentsToDelete.push_back({component, destroy});
    }

    void Session::deleteComponents()
    {
        for (auto &componentDelete: componentsToDelete)
        {
            auto it = std::find(components.begin(), components.end(), componentDelete.component);

            if (it != components.end())
                components.erase(it);

            if (componentDelete.destroy)
                delete componentDelete.component;
        }

        componentsToDelete.clear();
    }

} // fruitwork