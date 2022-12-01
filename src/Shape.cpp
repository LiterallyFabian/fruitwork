#include "Shape.h"

namespace fruitwork
{
    Shape::Shape(int x, int y, int w, int h, SDL_Color c) : Component(x, y, w, h), color(c)
    {
    }

} // fruitwork