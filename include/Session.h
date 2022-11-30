#ifndef FRUITWORK_SESSION_H
#define FRUITWORK_SESSION_H

#include <vector>
#include "Component.h"
#include "Scene.h"

namespace fruitwork
{

    class Session {

    public:
        /**
         * Add a component to the session.
         * @param component The component to add.
         */
        void add_component(Component *component);

        /**
         * Remove a component from the session.
         * @param component The component to remove.
         * @param destroy If true, the component will be destroyed.
         */
        void remove_component(Component *component, bool destroy = false);

        /**
         * Deletes all components that have been marked for deletion.
         */
        void deleteComponents();

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
    };

} // fruitwork

#endif //FRUITWORK_SESSION_H
