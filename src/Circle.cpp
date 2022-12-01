#include "Circle.h"
#include "System.h"

namespace fruitwork
{

    Circle *fruitwork::Circle::getInstance(int x, int y, int r, SDL_Color c)
    {
        return new Circle(x, y, r, c);
    }

    fruitwork::Circle::Circle(int x, int y, int r, SDL_Color c) : Shape(x, y, r, r, c), radius(r)
    {
        // x is the top left corner, centerX is the center of the circle
        this->centerX = x + r;
        this->centerY = y + r;
    }

    void fruitwork::Circle::draw() const
    {
        SDL_SetRenderDrawColor(sys.get_renderer(), color.r, color.g, color.b, color.a);
        SDL_SetRenderDrawBlendMode(sys.get_renderer(), SDL_BLENDMODE_BLEND); // respect alpha

        // draw circle
        // @see https://stackoverflow.com/a/24453110/11420970
        int r2 = radius * radius;
        int area = r2 << 2;
        int rr = radius << 1;

        for (int i = 0; i < area; i++)
        {
            int tx = i % rr - radius;
            int ty = i / rr - radius;
            if (tx * tx + ty * ty <= r2)
            {
                SDL_RenderDrawPoint(sys.get_renderer(), centerX + tx, centerY + ty);
            }
        }

        // reset
        SDL_SetRenderDrawColor(sys.get_renderer(), 255, 255, 255, 255);
        SDL_SetRenderDrawBlendMode(sys.get_renderer(), SDL_BLENDMODE_NONE);
    }

} // fruitwork