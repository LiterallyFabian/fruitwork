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

    private:
        /** Draw the rectangle with rotation. This is slightly more expensive than drawNormal, but with rotation support. */
        void drawRotated() const;

        /** Draw the rectangle without rotation. This method of doing it is cheaper, but rotation is not supported. */
        void drawNormal() const;
    };

} // fruitwork

#endif //FRUITWORK_RECTANGLE_H
