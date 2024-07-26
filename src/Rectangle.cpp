#include "Rectangle.h"
#include "System.h"

namespace fruitwork
{
    Rectangle *fruitwork::Rectangle::getInstance(int x, int y, int w, int h, SDL_Color c)
    {
        return new Rectangle(x, y, w, h, c);
    }

    fruitwork::Rectangle::Rectangle(int x, int y, int w, int h, SDL_Color c) : Shape(x, y, w, h, c) {}

    void fruitwork::Rectangle::draw() const
    {
        SDL_SetRenderDrawColor(sys.getRenderer(), color.r, color.g, color.b, color.a);
        SDL_SetRenderDrawBlendMode(sys.getRenderer(), SDL_BLENDMODE_BLEND); // respect alpha
        SDL_RenderFillRect(sys.getRenderer(), &getAbsoluteRect());

        // reset
        SDL_SetRenderDrawColor(sys.getRenderer(), 255, 255, 255, 255);
        SDL_SetRenderDrawBlendMode(sys.getRenderer(), SDL_BLENDMODE_NONE);
    }

} // fruitwork