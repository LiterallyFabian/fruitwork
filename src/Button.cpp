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
        SDL_Surface *surf = TTF_RenderText_Blended(fruitwork::sys.getFont(), text.c_str(), textColor);
        textTexture = SDL_CreateTextureFromSurface(fruitwork::sys.getRenderer(), surf);
        SDL_FreeSurface(surf);

        // todo: only load textures if they are not already loaded?
        buttonTextureLeft = IMG_LoadTexture(fruitwork::sys.getRenderer(), ResourceManager::getTexturePath("button-left.png").c_str());
        buttonTextureMiddle = IMG_LoadTexture(fruitwork::sys.getRenderer(), ResourceManager::getTexturePath("button-middle.png").c_str());
        buttonTextureRight = IMG_LoadTexture(fruitwork::sys.getRenderer(), ResourceManager::getTexturePath("button-right.png").c_str());

        clickSound = Mix_LoadWAV(ResourceManager::getAudioPath("click.wav").c_str());
        hoverSound = Mix_LoadWAV(ResourceManager::getAudioPath("hover.wav").c_str());

        if (font == nullptr)
        {
            font = TTF_OpenFont(constants::gDefaultFontPath.c_str(), 64);
        }
    }

    Button *Button::getInstance(int x, int y, int w, int h, std::string txt)
    {
        return new Button(x, y, w, h, txt);
    }

    void Button::draw() const
    {
        SDL_Rect rect = getRect();

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

        SDL_RenderCopy(sys.getRenderer(), buttonTextureLeft, nullptr, &leftRect);
        SDL_RenderCopy(sys.getRenderer(), buttonTextureMiddle, nullptr, &middleRect);
        SDL_RenderCopy(sys.getRenderer(), buttonTextureRight, nullptr, &rightRect);

        // the text should be centered, and have a 10% margin on all sides
        SDL_Rect textRect = {rect.x + 10, rect.y + 10, rect.w - 20, rect.h - 20};
        int w, h;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &w, &h);
        textRect.w = w;
        textRect.h = h;
        // center text in button
        textRect.x += (rect.w - 20 - w) / 2;
        textRect.y += (rect.h - 20 - h) / 2;
        SDL_RenderCopy(sys.getRenderer(), textTexture, nullptr, &textRect);
    }

    void Button::update()
    {
        SDL_Point mousePos = {0, 0};
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        if (!isDown)
        {
            if (SDL_PointInRect(&mousePos, &getRect()))
                setState(Button::State::HOVER);
            else
                setState(Button::State::NORMAL);
        }
    }

    Button::~Button()
    {
        SDL_DestroyTexture(textTexture);
        SDL_DestroyTexture(buttonTextureLeft);
        SDL_DestroyTexture(buttonTextureMiddle);
        SDL_DestroyTexture(buttonTextureRight);
        Mix_FreeChunk(clickSound);
        Mix_FreeChunk(hoverSound);

        SDL_SetCursor(sys.getCursorDefault()); // reset cursor
    }

    void Button::onMouseDown(const SDL_Event &event)
    {
        SDL_Point p = {event.button.x, event.button.y};

        if (SDL_PointInRect(&p, &getRect()))
        {
            if (onClick != nullptr)
                onClick(this);

            isDown = true;
            setState(Button::State::PRESSED);
        }
    }

    void Button::onMouseUp(const SDL_Event &)
    {
        if (isDown)
        {
            isDown = false;
            setState(Button::State::PRESSED);
        }
    }

    void Button::registerCallback(const std::function<void(Button*)>& callback)
    {
        onClick = callback;
    }

    void Button::setTextColor(const SDL_Color &color)
    {
        textColor = color;
        SDL_DestroyTexture(textTexture);
        SDL_Surface *surf = TTF_RenderText_Blended(sys.getFont(), text.c_str(), textColor);
        textTexture = SDL_CreateTextureFromSurface(sys.getRenderer(), surf);
        SDL_FreeSurface(surf);
    }

    void Button::setColor(const SDL_Color &color)
    {
        buttonColor = color;
    }

    void Button::setState(Button::State s)
    {
        if (s == state)
            return;

        switch (s)
        {
            case State::HOVER:
            {
                if (state == State::NORMAL)
                    Mix_PlayChannel(-1, hoverSound, 0);

                SDL_SetCursor(sys.getCursorPointer());
                break;
            }
            case State::PRESSED:
            {
                SDL_SetCursor(sys.getCursorPointer());
                Mix_PlayChannel(-1, clickSound, 0);
                break;
            }
            case State::NORMAL:
            {
                SDL_SetCursor(sys.getCursorDefault());
                break;
            }
        }

        state = s;
    }

    TTF_Font *Button::font = nullptr;

} // fruitwork