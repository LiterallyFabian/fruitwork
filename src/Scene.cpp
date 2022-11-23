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

    void Scene::remove_component(Component *component)
    {
        components.erase(std::remove(components.begin(), components.end(), component), components.end());
    }

} // fruitwork