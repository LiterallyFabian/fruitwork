#ifndef YUZU_CATCH_RECTANGLE_H
#define YUZU_CATCH_RECTANGLE_H

#include "Shape.h"

namespace fruitwork
{

    class Rectangle : public Shape {
    public:
        static Rectangle *getInstance(int x, int y, int w, int h, SDL_Color c);

        void draw() const override;

    protected:
        Rectangle(int x, int y, int w, int h, SDL_Color c);
    };

} // fruitwork

#endif //YUZU_CATCH_RECTANGLE_H
