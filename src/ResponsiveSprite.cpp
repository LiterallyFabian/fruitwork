#include "ResponsiveSprite.h"
#include "System.h"

namespace fruitwork
{
    ResponsiveSprite *ResponsiveSprite::getInstance(int x, int y, int w, int h, const std::string &textureName)
    {
        return new ResponsiveSprite(x, y, w, h, textureName);
    }

    ResponsiveSprite::ResponsiveSprite(int x, int y, int w, int h, const std::string &textureName)
            : Sprite(x, y, w, h, textureName) {}

    void ResponsiveSprite::draw() const
    {
        SDL_Rect r = get_rect();

        if (r.w > r.h) // a landscape image
        {
            r.w = r.h;
        }
        else
        {
            r.h = r.w;
        }

        SDL_RenderCopy(sys.get_renderer(), spriteTexture, nullptr, &r);
    }
} // fruitwork