#include "System.h"
#include "Constants.h"
#include "Sprite.h"

#include <SDL_image.h>

namespace fruitwork
{
    Sprite::Sprite(int x, int y, int w, int h, const std::string &texturePath, bool keepSurface) : Component(x, y, w, h), isTextureOwner(true)
    {
        surface = IMG_Load(texturePath.c_str());
        spriteTexture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);

        if (keepSurface)
            SDL_SetTextureBlendMode(spriteTexture, SDL_BLENDMODE_BLEND);
        else
        {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }

        if (spriteTexture == nullptr)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s", SDL_GetError());
    }

    Sprite::Sprite(int x, int y, int w, int h, SDL_Texture *texture) : Component(x, y, w, h), spriteTexture(texture), isTextureOwner(false) {}

    Sprite *Sprite::getInstance(int x, int y, int w, int h, const std::string &texturePath, bool keepSurface)
    {
        return new Sprite(x, y, w, h, texturePath, keepSurface);
    }

    Sprite *Sprite::getInstance(int x, int y, int w, int h, SDL_Texture *texture)
    {
        return new Sprite(x, y, w, h, texture);
    }

    void Sprite::draw() const
    {
        if (spriteTexture == nullptr)
            return;

        SDL_SetTextureColorMod(spriteTexture, colorMod.r, colorMod.g, colorMod.b);
        SDL_SetTextureAlphaMod(spriteTexture, alphaMod);
        SDL_Rect rect = getRect();
        SDL_RenderCopyEx(sys.getRenderer(), spriteTexture, nullptr, &rect, 0, nullptr, flipType);
    }

    Sprite::~Sprite()
    {
        if (isTextureOwner)
            SDL_DestroyTexture(spriteTexture);

        if (isSurfaceOwner)
            SDL_FreeSurface(surface);
    }

    void fruitwork::Sprite::setTexture(const std::string &texturePath)
    {
        if (isTextureOwner)
            SDL_DestroyTexture(spriteTexture);

        if (isSurfaceOwner)
        {
            SDL_FreeSurface(surface);
            isSurfaceOwner = false;
            surface = nullptr;
        }

        surface = IMG_Load(texturePath.c_str());
        isTextureOwner = true;
    }

    void fruitwork::Sprite::setTexture(const std::string &texturePath, bool keepSurface)
    {
        if (isTextureOwner)
            SDL_DestroyTexture(spriteTexture);

        if (isSurfaceOwner)
        {
            SDL_FreeSurface(surface);
            isSurfaceOwner = false;
            surface = nullptr;
        }

        surface = IMG_Load(texturePath.c_str());
        spriteTexture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);

        isTextureOwner = true;

        if (keepSurface)
        {
            isSurfaceOwner = true;
        }
        else
        {
            SDL_FreeSurface(surface);
            surface = nullptr;
            isSurfaceOwner = false;
        }
    }

    void fruitwork::Sprite::setTexture(SDL_Texture *texture)
    {
        if (isTextureOwner)
            SDL_DestroyTexture(spriteTexture);

        if (isSurfaceOwner)
        {
            SDL_FreeSurface(surface);
            isSurfaceOwner = false;
            surface = nullptr;
        }

        spriteTexture = texture;
        isTextureOwner = false;
    }

#pragma region Collision Detection

    bool Sprite::rectCollidesWith(const Sprite *other) const
    {
        SDL_Rect rect1 = getRect();
        SDL_Rect rect2 = other->getRect();
        return SDL_HasIntersection(&rect1, &rect2);
    }

    inline static Uint32 getPixel(SDL_Surface *surface, int x, int y)
    {
        SDL_LockSurface(surface);
        int bpp = surface->format->BytesPerPixel;
        Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
        Uint32 pixel;

        switch (bpp) // NOLINT(hicpp-multiway-paths-covered) - a default case is not needed
        {
            case 1:
                pixel = *p;
                break;

            case 2:
                pixel = *(Uint16 *) p;
                break;

            case 3:
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN) // NOLINT
                    pixel = p[0] << 16 | p[1] << 8 | p[2];
                else
                    pixel = p[0] | p[1] << 8 | p[2] << 16;
                break;

            case 4:
                pixel = *(Uint32 *) p;
                break;
        }

        SDL_UnlockSurface(surface);
        return pixel;
    }

    bool Sprite::pixelCollidesWith(const Sprite *other, Uint8 alpha) const
    {
        if (surface == nullptr || other->surface == nullptr)
        {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Cannot check pixel collision with a sprite that has no surface. Returning false.");
            return false;
        }

        SDL_Rect rect1 = getRect();
        SDL_Rect rect2 = other->getRect();

        if (!rectCollidesWith(other))
            return false; // no point of trying if not even the rects collide

        SDL_Rect intersection;
        SDL_IntersectRect(&rect1, &rect2, &intersection);

        for (int x = intersection.x; x < intersection.x + intersection.w; x++)
        {
            for (int y = intersection.y; y < intersection.y + intersection.h; y++)
            {
                Uint32 pixel1 = getPixel(surface, x - rect1.x, y - rect1.y);
                Uint32 pixel2 = getPixel(other->surface, x - rect2.x, y - rect2.y);

                Uint8 r1, g1, b1, a1;
                Uint8 r2, g2, b2, a2;

                SDL_GetRGBA(pixel1, surface->format, &r1, &g1, &b1, &a1);
                SDL_GetRGBA(pixel2, other->surface->format, &r2, &g2, &b2, &a2);

                if (a1 > alpha && a2 > alpha)
                    return true;
            }
        }

        return false;
    }

#pragma endregion

} // fruitwork