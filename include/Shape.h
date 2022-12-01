#ifndef FRUITWORK_SHAPE_H
#define FRUITWORK_SHAPE_H

#include "Component.h"

namespace fruitwork
{

    class Shape : public Component {
    public:
        void setColor(SDL_Color c) { this->color = c; }

        void draw() const override = 0;

    protected:
        Shape(int x, int y, int w, int h, SDL_Color c);

        SDL_Color color;
    };

} // fruitwork

#endif //FRUITWORK_SHAPE_H
