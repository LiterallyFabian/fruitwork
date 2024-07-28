#include "Rectangle.h"
#include "System.h"

namespace fruitwork
{
    Rectangle *fruitwork::Rectangle::getInstance(int x, int y, int w, int h, SDL_Color c)
    {
        return new Rectangle(x, y, w, h, c);
    }

    fruitwork::Rectangle::Rectangle(int x, int y, int w, int h, SDL_Color c) : Shape(x, y, w, h, c) {}

    void fruitwork::Rectangle::draw() const
    {
        if (getAbsoluteAngle() == 0.0) // use the old way
            drawNormal();
        else
            drawRotated();
    }

    void Rectangle::drawNormal() const
    {
        SDL_Renderer *renderer = sys.getRenderer();

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // respect alpha
        SDL_RenderFillRect(renderer, &getAbsoluteRect());

        // reset
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }

    void Rectangle::drawRotated() const
    {
        SDL_Renderer *renderer = sys.getRenderer();
        SDL_Rect absRect = getAbsoluteRect();
        double angle = getAbsoluteAngle();
        SDL_Point pivot = getPivot();

        SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                                 SDL_TEXTUREACCESS_TARGET, absRect.w, absRect.h);

        // render to texture
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // respect alpha
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer);

        // draw rectangle to screen
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_RenderCopyEx(renderer, texture, nullptr, &absRect, -angle, &pivot, getFlip());

        // reset
        SDL_DestroyTexture(texture);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }

} // fruitwork