#include "ResponsiveSprite.h"
#include "System.h"

namespace fruitwork
{
    ResponsiveSprite *ResponsiveSprite::getInstance(int x, int y, int w, int h, const std::string &textureName, Alignment alignment)
    {
        return new ResponsiveSprite(x, y, w, h, textureName, alignment);
    }

    ResponsiveSprite::ResponsiveSprite(int x, int y, int w, int h, const std::string &textureName, Alignment alignment)
            : Sprite(x, y, w, h, textureName), alignment(alignment) {}

    void ResponsiveSprite::start()
    {
        SDL_Rect r = get_rect();

        if (r.w > r.h) // a landscape image, width is greater than height
            r.w = r.h;
        else
            r.h = r.w;

        switch (alignment)
        {
            case Alignment::TOP_LEFT:
                break;
            case Alignment::TOP_CENTER: // move right by half the difference
                r.x += (get_rect().w - r.w) / 2;
                break;
            case Alignment::TOP_RIGHT: // move right by the difference
                r.x += get_rect().w - r.w;
                break;
            case Alignment::CENTER_LEFT: // move down by half the difference
                r.y += (get_rect().h - r.h) / 2;
                break;
            case Alignment::CENTER: // move right by half the difference, then down by half the difference
                r.x += (get_rect().w - r.w) / 2;
                r.y += (get_rect().h - r.h) / 2;
                break;
            case Alignment::CENTER_RIGHT:
                r.x += get_rect().w - r.w;
                r.y += (get_rect().h - r.h) / 2;
                break;
            case Alignment::BOTTOM_LEFT:
                r.y += get_rect().h - r.h;
                break;
            case Alignment::BOTTOM_CENTER:
                r.x += (get_rect().w - r.w) / 2;
                r.y += get_rect().h - r.h;
                break;
            case Alignment::BOTTOM_RIGHT:
                r.x += get_rect().w - r.w;
                r.y += get_rect().h - r.h;
                break;
        }

        set_rect(r);
    }
} // fruitwork