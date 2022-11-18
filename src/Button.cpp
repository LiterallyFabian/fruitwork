#include <iostream>
#include "Button.h"
#include "System.h"
#include "SDL_image.h"
#include "Constants.h"
#include "Component.h"
#include "ResourceManager.h"

namespace fruitwork
{
    Button::Button(int x, int y, int w, int h, std::string text) : Component(x, y, w, h), text(text)
    {
        SDL_Surface *surf = TTF_RenderText_Solid(fruitwork::sys.get_font(), text.c_str(), textColor);
        textTexture = SDL_CreateTextureFromSurface(fruitwork::sys.get_renderer(), surf);
        SDL_FreeSurface(surf);

        buttonTextureLeft = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button-left.png").c_str());
        buttonTextureMiddle = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button-middle.png").c_str());
        buttonTextureRight = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button-right.png").c_str());
    }

    Button *Button::getInstance(int x, int y, int w, int h, std::string txt)
    {
        return new Button(x, y, w, h, txt);
    }

    void Button::draw() const
    {
        SDL_Rect rect = get_rect();

        switch (state)
        {
            case Button::State::PRESSED:
            {
                const double mod = 0.8;
                SDL_SetTextureColorMod(buttonTextureLeft, buttonColor.r * mod, buttonColor.g * mod, buttonColor.b * mod);
                SDL_SetTextureColorMod(buttonTextureMiddle, buttonColor.r * mod, buttonColor.g * mod, buttonColor.b * mod);
                SDL_SetTextureColorMod(buttonTextureRight, buttonColor.r * mod, buttonColor.g * mod, buttonColor.b * mod);

                rect.x += 2;
                rect.y += 2;
                rect.w -= 4;
                rect.h -= 4;
                break;
            }
            case Button::State::HOVER:
            {
                const double mod = 0.95;
                SDL_SetTextureColorMod(buttonTextureLeft, buttonColor.r * mod, buttonColor.g * mod, buttonColor.b * mod);
                SDL_SetTextureColorMod(buttonTextureMiddle, buttonColor.r * mod, buttonColor.g * mod, buttonColor.b * mod);
                SDL_SetTextureColorMod(buttonTextureRight, buttonColor.r * mod, buttonColor.g * mod, buttonColor.b * mod);
                break;
            }

            case Button::State::NORMAL:
            {
                SDL_SetTextureColorMod(buttonTextureLeft, buttonColor.r, buttonColor.g, buttonColor.b);
                SDL_SetTextureColorMod(buttonTextureMiddle, buttonColor.r, buttonColor.g, buttonColor.b);
                SDL_SetTextureColorMod(buttonTextureRight, buttonColor.r, buttonColor.g, buttonColor.b);
                break;
            }
        }

        SDL_Rect leftRect = {rect.x, rect.y, 8, rect.h};
        SDL_Rect middleRect = {rect.x + 8, rect.y, rect.w - 16, rect.h};
        SDL_Rect rightRect = {rect.x + rect.w - 8, rect.y, 8, rect.h};

        SDL_RenderCopy(fruitwork::sys.get_renderer(), buttonTextureLeft, nullptr, &leftRect);
        SDL_RenderCopy(fruitwork::sys.get_renderer(), buttonTextureMiddle, nullptr, &middleRect);
        SDL_RenderCopy(fruitwork::sys.get_renderer(), buttonTextureRight, nullptr, &rightRect);

        // draw text with padding
        SDL_Rect textRect = {rect.x + 10, rect.y + 10, rect.w - 20, rect.h - 20};
        SDL_RenderCopy(fruitwork::sys.get_renderer(), textTexture, nullptr, &textRect);
    }

    void Button::update()
    {
        SDL_Point mousePos = {0, 0};
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        if (!isDown)
        {
            if (SDL_PointInRect(&mousePos, &get_rect()))
                state = Button::State::HOVER;
            else
                state = Button::State::NORMAL;
        }
    }

    Button::~Button()
    {
        SDL_DestroyTexture(textTexture);
        SDL_DestroyTexture(buttonTextureLeft);
        SDL_DestroyTexture(buttonTextureMiddle);
        SDL_DestroyTexture(buttonTextureRight);
    }

    void Button::onMouseDown(const SDL_Event &event)
    {
        SDL_Point p = {event.button.x, event.button.y};

        if (SDL_PointInRect(&p, &get_rect()))
        {
            if (onClick != nullptr)
                onClick(this);

            isDown = true;
            state = Button::State::PRESSED;
        }
    }

    void Button::onMouseUp(const SDL_Event &)
    {
        isDown = false;
        state = Button::State::NORMAL;
    }

    void Button::registerCallback(void (*callback)(Button *source))
    {
        onClick = callback;
    }

    void Button::setTextColor(const SDL_Color &color)
    {
        textColor = color;
        SDL_DestroyTexture(textTexture);
        SDL_Surface *surf = TTF_RenderText_Solid(fruitwork::sys.get_font(), text.c_str(), textColor);
        textTexture = SDL_CreateTextureFromSurface(fruitwork::sys.get_renderer(), surf);
        SDL_FreeSurface(surf);
    }

    void Button::setColor(const SDL_Color &color)
    {
        buttonColor = color;
    }

} // fruitwork