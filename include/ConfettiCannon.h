#ifndef FRUITWORK_CONFETTI_CANNON_H
#define FRUITWORK_CONFETTI_CANNON_H

#include <SDL_rect.h>
#include "Component.h"
#include "Rectangle.h"
#include "Sprite.h"

namespace fruitwork
{

    class ConfettiCannon : public Component {
    public:
        /**
         *
         * @param w The width of each confetti.
         * @param h The height of each confetti.
         */
        static ConfettiCannon *getInstance(int x, int y, int w, int h, const std::string &texturePath);

        ~ConfettiCannon() override;

        void draw() const override;

        void update(float elapsedTime) override;

        /***
         * Fires a confetti cannon.
         * @param angle The angle the confetti will be fired at.
         * @param spread The spread of the confetti. An angle of 45 and a spread of 10 will fire confetti at angles 35 to 55.
         * @param amount The amount of confetti to fire.
         * @param time The time it takes for all confetti to be fired.
         * @param fadeOutTime The time it takes for the confetti to fade out.
         */
        void fire(float angle, int spread, int amount, int time, int fadeOutTime = -1);

        void setColors(std::vector<SDL_Color> colors) { this->colors = colors; }

    private:
        explicit ConfettiCannon(int x, int y, int w, int h, const std::string &texturePath);

        SDL_Texture *texture;

        // pastel colors
        std::vector<SDL_Color> colors = {
                {255, 153, 153},
                {255, 102, 178},
                {255, 153, 204},
                {255, 204, 153},
                {255, 255, 153},
                {204, 255, 153},
                {153, 255, 153},
                {153, 255, 204},
                {153, 255, 255},
                {153, 204, 255},
                {153, 153, 255},
                {204, 153, 255},
                {255, 153, 255}
        };

        struct Confetti {
            Sprite *sprite = nullptr;
            SDL_FPoint force = {0, 0};
            Uint64 startTime = 0;
            bool started = false;
            int fadeOutTime = -1;

            ~Confetti()
            {
                delete sprite;
            }
        };

        std::vector<Confetti *> confetti;
    };


} // fruitwork

#endif //FRUITWORK_CONFETTI_CANNON_H
