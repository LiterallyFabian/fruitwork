#ifndef YUZU_CATCH_COVERINGSPRITE_H
#define YUZU_CATCH_COVERINGSPRITE_H

#include "Sprite.h"

namespace fruitwork
{
    /**
     * A covering sprite is a sprite that covers the whole rect, it can however overflow.
     * This is mainly useful for backgrounds.
     */
    class CoveringSprite : public Sprite {
    public:
        static CoveringSprite *getInstance(int x, int y, int w, int h, const std::string &texturePath);

        static CoveringSprite *getInstance(int x, int y, int w, int h, SDL_Texture *texture);

        void start() override;

        void setTexture(const std::string &texturePath) override;

        void setTexture(SDL_Texture *texture) override;

    protected:
        CoveringSprite(int x, int y, int w, int h, const std::string &texturePath);

        CoveringSprite(int x, int y, int w, int h, SDL_Texture *texture);

    private:
        SDL_Rect originalRect;

        void updateRect();
    };

} // fruitwork

#endif //YUZU_CATCH_COVERINGSPRITE_H
