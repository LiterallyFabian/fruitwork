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
        static const SDL_Color color = {0, 0, 0, 255}; // black
        SDL_Surface *surf = TTF_RenderText_Solid(fruitwork::sys.get_font(), text.c_str(), color);
        textTexture = SDL_CreateTextureFromSurface(fruitwork::sys.get_renderer(), surf);
        SDL_FreeSurface(surf);

        buttonTexture = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button.png").c_str());
        buttonTextureDown = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button_down.png").c_str());
    }

    Button *Button::getInstance(int x, int y, int w, int h, std::string txt)
    {
        return new Button(x, y, w, h, txt);
    }

    void Button::draw() const
    {
        SDL_Texture *texture = isDown ? buttonTextureDown : buttonTexture;
        SDL_RenderCopy(fruitwork::sys.get_renderer(), texture, nullptr, &get_rect());

        SDL_Rect textRect = get_rect();
        textRect.x += 10;
        textRect.y += 10;
        textRect.w -= 20;
        textRect.h -= 20;

        SDL_RenderCopy(fruitwork::sys.get_renderer(), textTexture, nullptr, &textRect);
    }

    Button::~Button()
    {
        SDL_DestroyTexture(textTexture);
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(buttonTextureDown);
    }

    void Button::onMouseDown(const SDL_Event &event)
    {
        SDL_Point p = {event.button.x, event.button.y};

        if (SDL_PointInRect(&p, &get_rect()))
        {
            if(onClick != nullptr)
                onClick(this);
            isDown = true;
        }
    }

    void Button::onMouseUp(const SDL_Event &)
    {
        isDown = false;
    }

    void Button::registerCallback(void (*callback)(Button *source))
    {
        onClick = callback;
    }

    std::string Button::getText() const
    {
        return text;
    }

} // fruitwork