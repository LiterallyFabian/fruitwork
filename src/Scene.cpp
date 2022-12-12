#include "Scene.h"
#include "Component.h"
#include <algorithm>

namespace fruitwork
{

    void Scene::add_component(Component *component)
    {
        components.push_back(component);

        // sort components by z-index
        // stable_sort is slower than sort, but it keeps the order of components with the same z-index intact
        // @see https://stackoverflow.com/a/34668459/11420970
        std::stable_sort(components.begin(), components.end(), [](Component *a, Component *b)
        {
            return a->z_index() < b->z_index();
        });

        component->start();
    }

    void Scene::add_component(Component *component, int z_index)
    {
        component->set_z_index(z_index);
        add_component(component);
    }

    void Scene::remove_component(Component *component, bool destroy)
    {
        componentsToDelete.push_back({component, destroy});
    }

    void Scene::deleteComponents()
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