#ifndef FRUITWORK_RECTANGLE_H
#define FRUITWORK_RECTANGLE_H

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

#endif //FRUITWORK_RECTANGLE_H
