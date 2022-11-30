#ifndef FRUITWORK_SCENE_H
#define FRUITWORK_SCENE_H

#include <SDL.h>
#include <vector>
#include "Component.h"

namespace fruitwork
{

    /**
     * @brief A Scene, also commonly known as a Stage, GameState or Screen, is a container for all the objects in said screen.
     * Scene is abstract and must be inherited from to be used.
     */
    class Scene {
    public:

        /**
         * Add a component to the scene. Added components will automatically be started, drawn and updated.
         * @param component The component to add.
         */
        void add_component(Component *component);

        /**
         * Remove a component from the scene.
         * @param component The component to remove.
         * @param destroy If true, the component will be destroyed.
         */
        void remove_component(Component *component, bool destroy = false);

        std::vector<Component *> get_components() const { return components; }

        /**
         * Deletes all components that have been marked for deletion.
         */
        void deleteComponents();

        /**
         * Called when this Scene is loaded.
         * @return true if the Scene was loaded successfully, false otherwise.
         */
        virtual bool enter() = 0;

        /**
         * Called when this Scene is unloaded. Textures and other resources should be freed here.
         * @return true if the Scene was unloaded successfully, false otherwise.
         */
        virtual bool exit() = 0;

        /**
         * Called when an SDL_Event is received.
         * @param e The SDL_Event received.
         */
        virtual void handleEvent(SDL_Event &e) {}

        /**
         * Update is called every frame, before draw.
         */
        virtual void update() {}

        /**
         * Draw is called every frame, after update.
         */
        virtual void draw() {}

        virtual ~Scene() = default;


    protected:
        std::vector<Component *> components;

    private:
        struct ComponentDelete {
            Component *component;
            bool destroy;
        };

        std::vector<ComponentDelete> componentsToDelete;
    };

} // fruitwork

#endif //FRUITWORK_SCENE_H
