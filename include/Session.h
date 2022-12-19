#ifndef FRUITWORK_SESSION_H
#define FRUITWORK_SESSION_H

#include <vector>
#include "Component.h"
#include "Scene.h"
#include <map>
#include <functional>

namespace fruitwork
{

    class Session {

    public:
        /**
         * Add a component to the session.
         * @param component The component to add.
         */
        void addComponent(Component *component);

        /**
         * Remove a component from the session.
         * @param component The component to remove.
         * @param destroy If true, the component will be destroyed.
         */
        void removeComponent(Component *component, bool destroy = false);

        /**
         * Register a keyboard event handler.
         * @tparam T The type of the object that will handle the event.
         * @param key The key to trigger the event.
         * @param handler The handler function.
         */
        void registerKeyboardEvent(SDL_Keycode key, const std::function<void()> &callback)
        {
            keyboardEventHandlers[key] = callback;
        }

        /**
         * De-register a keyboard event handler.
         * @param key The key to trigger the event.
         * @return True if the event handler was found and removed, false otherwise.
         */
        bool deregisterKeyboardEvent(SDL_Keycode key)
        {
            return keyboardEventHandlers.erase(key) > 0;
        }

        /**
         * Run the session.
         * @param startScene The scene to start the session with.
         */
        void run(Scene *startScene);

        ~Session();

    private:
        struct ComponentDelete {
            Component *component;
            bool destroy;
        };

        std::vector<Component *> components;
        std::vector<ComponentDelete> componentsToDelete;

        std::map<SDL_Keycode, std::function<void()>> keyboardEventHandlers;

        /**
         * Deletes all components that have been marked for deletion.
         */
        void deleteComponents();
    };
} // fruitwork

#endif //FRUITWORK_SESSION_H
