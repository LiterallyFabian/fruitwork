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
        sprite = ResponsiveSprite::getInstance(0, 0, w, h, texturePath);
        isSpriteOwner = true;
    }

    ImageButton::ImageButton(int x, int y, int w, int h, SDL_Texture *texture) : Button(x, y, w, h, "")
    {
        sprite = ResponsiveSprite::getInstance(0, 0, w, h, texture);
        isSpriteOwner = false;
    }

    void ImageButton::start()
    {
        Button::start();
        sprite->start();

        originalRect = sprite->getRect();
    }

    void ImageButton::draw() const
    {
        SDL_Rect rect = originalRect;

        switch (state)
        {
            case Button::State::PRESSED:
            {
                const double mod = 0.8;
                sprite->setColorMod({static_cast<Uint8>(buttonColor.r * mod), static_cast<Uint8>(buttonColor.g * mod), static_cast<Uint8>(buttonColor.b * mod)});

                rect.x += 2;
                rect.y += 2;
                rect.w -= 4;
                rect.h -= 4;
                break;
            }
            case Button::State::HOVER:
            {
                const double mod = 0.95;
                sprite->setColorMod({static_cast<Uint8>(buttonColor.r * mod), static_cast<Uint8>(buttonColor.g * mod), static_cast<Uint8>(buttonColor.b * mod)});
                break;
            }

            case Button::State::NORMAL:
            {
                sprite->setColorMod({buttonColor.r, buttonColor.g, buttonColor.b});
                break;
            }
        }

        rect.x += getRect().x;
        rect.y += getRect().y;

        sprite->setFlip(getFlip());
        sprite->setRect(rect);
        sprite->draw();
    }

    ImageButton::~ImageButton()
    {
        delete sprite;
    }


} // fruitwork