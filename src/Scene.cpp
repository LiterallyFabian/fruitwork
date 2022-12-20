#include "Scene.h"
#include "Component.h"
#include <algorithm>

namespace fruitwork
{

    void Scene::addComponent(Component *component)
    {
        components.push_back(component);

        // sort components by z-index
        // stable_sort is slower than sort, but it keeps the order of components with the same z-index intact
        // @see https://stackoverflow.com/a/34668459/11420970
        std::stable_sort(components.begin(), components.end(), [](Component *a, Component *b)
        {
            return a->zIndex() < b->zIndex();
        });

        component->start();
    }

    void Scene::addComponent(Component *component, int zIndex)
    {
        component->setZIndex(zIndex);
        addComponent(component);
    }

    void Scene::removeComponent(Component *component, bool destroy)
    {
        componentsToDelete.push_back({component, destroy});
    }

    void Scene::deleteComponents()
    {
        if (componentsToDelete.empty())
            return;

        SDL_Log("Deleting %d components", (int)componentsToDelete.size());

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