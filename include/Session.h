#ifndef FRUITWORK_SESSION_H
#define FRUITWORK_SESSION_H

#include <vector>
#include "Component.h"

namespace fruitwork
{

    class Session {

    public:
        /**
         * Add a component to the session.
         * @param component The component to add.
         */
        void add_component(Component *component);

        void run();

        ~Session();

    private:
        std::vector<Component *> components;
    };

} // fruitwork

#endif //FRUITWORK_SESSION_H
