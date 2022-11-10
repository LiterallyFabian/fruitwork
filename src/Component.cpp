#include "Component.h"

namespace fruitwork
{

    Component::Component(int x, int y, int w, int h) : rect{x, y, w, h}
    {

    }

    Component::~Component()
    = default;

} // fruitwork