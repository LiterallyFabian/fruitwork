#include "CoveringSprite.h"

namespace fruitwork
{
    CoveringSprite *fruitwork::CoveringSprite::getInstance(int x, int y, int w, int h, const std::string &texturePath)
    {
        return new CoveringSprite(x, y, w, h, texturePath);
    }

    CoveringSprite *CoveringSprite::getInstance(int x, int y, int w, int h, SDL_Texture *texture)
    {
        return new CoveringSprite(x, y, w, h, texture);
    }

    CoveringSprite::CoveringSprite(int x, int y, int w, int h, const std::string &texturePath) :
            Sprite(x, y, w, h, texturePath), originalRect({x, y, w, h}) {}

    CoveringSprite::CoveringSprite(int x, int y, int w, int h, SDL_Texture *texture) :
            Sprite(x, y, w, h, texture), originalRect({x, y, w, h}) {}

    void CoveringSprite::start()
    {
        updateRect();
    }

    void CoveringSprite::setTexture(const std::string &texturePath)
    {
        Sprite::setTexture(texturePath);
        updateRect();
    }

    void CoveringSprite::setTexture(SDL_Texture *texture)
    {
        Sprite::setTexture(texture);
        updateRect();
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

    void CoveringSprite::updateRect()
    {
        SDL_Rect original = originalRect;
        int w, h;
        SDL_QueryTexture(this->spriteTexture, nullptr, nullptr, &w, &h);

        float scale = std::max((float) original.w / w, (float) original.h / h);

        // the scaled image size
        int scaledW = w * scale;
        int scaledH = h * scale;

        // the offset to center the image
        int offsetX = (original.w - scaledW) / 2;
        int offsetY = (original.h - scaledH) / 2;

        SDL_Rect scaled = {original.x + offsetX, original.y + offsetY, scaledW, scaledH};
        set_rect(scaled);
    }

#pragma clang diagnostic pop


} // fruitwork