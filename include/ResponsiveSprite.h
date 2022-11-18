#ifndef FRUITWORK_RESPONSIVESPRITE_H
#define FRUITWORK_RESPONSIVESPRITE_H

#include "Sprite.h"

namespace fruitwork
{

    /**
     * A Sprite that will be resized to fit within its container, without stretching.
     */
    class ResponsiveSprite : public Sprite {
    public:

        static ResponsiveSprite *getInstance(int x, int y, int w, int h, const std::string &textureName);

        void draw() const override;

    protected:
        ResponsiveSprite(int x, int y, int w, int h, const std::string &textureName);
    };

} // fruitwork

#endif //FRUITWORK_RESPONSIVESPRITE_H
