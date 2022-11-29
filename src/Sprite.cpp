#include "System.h"
#include "Constants.h"
#include "Sprite.h"

#include <SDL_image.h>

namespace fruitwork
{
    Sprite::Sprite(int x, int y, int w, int h, const std::string &texturePath) : Component(x, y, w, h), isTextureOwner(true)
    {
        spriteTexture = IMG_LoadTexture(sys.get_renderer(), texturePath.c_str());
        if (spriteTexture == nullptr)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s", SDL_GetError());
    }

    Sprite::Sprite(int x, int y, int w, int h, SDL_Texture *texture) : Component(x, y, w, h), spriteTexture(texture), isTextureOwner(false) {}

    Sprite *Sprite::getInstance(int x, int y, int w, int h, const std::string &texturePath)
    {
        return new Sprite(x, y, w, h, texturePath);
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
        SDL_Rect rect = get_rect();
        SDL_RenderCopyEx(sys.get_renderer(), spriteTexture, nullptr, &rect, 0, nullptr, flipType);
    }

    Sprite::~Sprite()
    {
        if (isTextureOwner)
            SDL_DestroyTexture(spriteTexture);
    }

    void fruitwork::Sprite::setTexture(const std::string &texturePath)
    {
        if (isTextureOwner)
            SDL_DestroyTexture(spriteTexture);

        spriteTexture = IMG_LoadTexture(sys.get_renderer(), texturePath.c_str());
        isTextureOwner = true;
    }

    void fruitwork::Sprite::setTexture(SDL_Texture *texture)
    {
        if (isTextureOwner)
            SDL_DestroyTexture(spriteTexture);

        spriteTexture = texture;
        isTextureOwner = false;
    }
} // fruitwork