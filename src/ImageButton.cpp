#include <SDL_image.h>
#include "ImageButton.h"
#include "System.h"

namespace fruitwork
{
    ImageButton *ImageButton::getInstance(int x, int y, int w, int h, SDL_Texture *texture)
    {
        return new ImageButton(x, y, w, h, texture);
    }

    ImageButton *ImageButton::getInstance(int x, int y, int w, int h, const std::string &texturePath)
    {
        return new ImageButton(x, y, w, h, texturePath);
    }

    ImageButton::ImageButton(int x, int y, int w, int h, const std::string &texturePath) : Button(x, y, w, h, "")
    {
        texture = IMG_LoadTexture(sys.get_renderer(), texturePath.c_str());
        isSpriteOwner = true;
    }

    ImageButton::ImageButton(int x, int y, int w, int h, SDL_Texture *texture) : Button(x, y, w, h, "")
    {
        this->texture = texture;
        isSpriteOwner = false;
    }

    void ImageButton::draw() const
    {
        SDL_Rect rect = get_rect();

        switch (state)
        {
            case Button::State::PRESSED:
            {
                const double mod = 0.8;
                SDL_SetTextureColorMod(texture, static_cast<Uint8>(buttonColor.r * mod), static_cast<Uint8>(buttonColor.g * mod), static_cast<Uint8>(buttonColor.b * mod));

                rect.x += 2;
                rect.y += 2;
                rect.w -= 4;
                rect.h -= 4;
                break;
            }
            case Button::State::HOVER:
            {
                const double mod = 0.95;
                SDL_SetTextureColorMod(texture, static_cast<Uint8>(buttonColor.r * mod), static_cast<Uint8>(buttonColor.g * mod), static_cast<Uint8>(buttonColor.b * mod));
                break;
            }

            case Button::State::NORMAL:
            {
                SDL_SetTextureColorMod(texture, static_cast<Uint8>(buttonColor.r), static_cast<Uint8>(buttonColor.g), static_cast<Uint8>(buttonColor.b));
                break;
            }
        }

        SDL_RenderCopy(sys.get_renderer(), texture, nullptr, &rect);
    }

    ImageButton::~ImageButton()
    {
        if (isSpriteOwner)
            SDL_DestroyTexture(texture);
    }

} // fruitwork