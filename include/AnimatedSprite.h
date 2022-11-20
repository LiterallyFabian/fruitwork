#ifndef FRUITWORK_ANIMATEDSPRITE_H
#define FRUITWORK_ANIMATEDSPRITE_H

#include <vector>
#include "Sprite.h"

namespace fruitwork
{

    class AnimatedSprite : public Sprite {
    public:
        /**
         * Get an instance of the AnimatedSprite class.
         * @param x The x position of the sprite.
         * @param y The y position of the sprite.
         * @param w The width of the sprite.
         * @param h The height of the sprite.
         * @param animationName  The name of the animation to use. {n} will be replaced with the frame number.
         * @param animationSpeed  The speed of the animation, in milliseconds.
         * @return
         */
        static AnimatedSprite *getInstance(int x, int y, int w, int h, const std::string &animationName, int animationSpeed);

        void update() override;

        ~AnimatedSprite() override;

    protected:
        AnimatedSprite(int x, int y, int w, int h, const std::string &animationName, int animationSpeed);

    private:
        std::vector<SDL_Texture *> frames;
        int frameCount = 0;
        std::string animationName;
        int animationSpeed;

        int frame = 0;
        int lastFrame = 0;
    };

} // fruitwork

#endif //FRUITWORK_ANIMATEDSPRITE_H
