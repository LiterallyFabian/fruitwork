#include "Scene.h"
#include "Component.h"
#include <algorithm>

namespace fruitwork
{

    void Scene::add_component(Component *component)
    {
        components.push_back(component);
        component->start();
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
            {
                components.erase(it);
                if (componentDelete.destroy)
                    delete componentDelete.component;
            }
        }

        componentsToDelete.clear();
    }


} // fruitwork