#include <iostream>
#include "Scene.h"
#include "Component.h"

namespace fruitwork
{

    void Scene::add_component(Component *component)
    {
        components.push_back(component);
        component->start();
    }

} // fruitwork