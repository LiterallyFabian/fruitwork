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
         */
        void remove_component(Component *component);

        /**
         * Run the session.
         * @param startScene The scene to start the session with.
         */
        void run(Scene *startScene);

        ~Session();

    private:
        std::vector<Component *> components;
    };

} // fruitwork

#endif //FRUITWORK_SESSION_H
