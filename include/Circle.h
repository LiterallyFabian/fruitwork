#ifndef FRUITWORK_CIRCLE_H
#define FRUITWORK_CIRCLE_H

#include "Shape.h"

namespace fruitwork
{

    class Circle : public Shape {
    public:
        static Circle *getInstance(int x, int y, int r, SDL_Color c);

        void draw() const override;

    protected:
        Circle(int x, int y, int r, SDL_Color c);

    private:
        int radius;
        int centerX, centerY;
    };

} // fruitwork

#endif //FRUITWORK_CIRCLE_H
