#include "Label.h"
#include "System.h"
#include "Constants.h"
#include <SDL_ttf.h>
#include <iostream>
#include "ResourceManager.h"

namespace fruitwork
{
    Label *Label::getInstance(int x, int y, int w, int h, const std::string &text)
    {
        return new Label(x, y, w, h, text);
    }

    Label::Label(int x, int y, int w, int h, // NOLINT
                 const std::string &text) : Component(x, y, w, h), text(text)
    {
        setText(text);
    }

    void Label::draw() const
    {
        SDL_RenderCopy(sys.get_renderer(), texture, nullptr, &drawRect);
    }

    Label::~Label()
    {
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }

    std::string Label::getText() const { return text; }

    void Label::setText(const std::string &t)
    {
        text = t;

        SDL_DestroyTexture(texture);

        // make text smaller if needed to prevent stretch
        TTF_CloseFont(font);
        font = TTF_OpenFont(ResourceManager::getFontPath("KGRedHands").c_str(), fontSize);

        SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(sys.get_renderer(), surf);
        SDL_FreeSurface(surf);

        // set the draw rect
        drawRect = get_rect();
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        switch (alignment)
        {
            case Alignment::LEFT:
                drawRect.w = w;
                drawRect.h = h;
                break;
            case Alignment::CENTER:
                drawRect.w = w;
                drawRect.h = h;
                drawRect.x += (get_rect().w - w) / 2;
                break;
            case Alignment::RIGHT:
                drawRect.w = w;
                drawRect.h = h;
                drawRect.x += get_rect().w - w;
                break;
        }
    }

    void Label::setColor(const SDL_Color &c)
    {
        this->color = c;
        setText(text);
    }

    void Label::setFontSize(const int size)
    {
        this->fontSize = size;
        setText(text);
    }

    void Label::setAlignment(Label::Alignment a)
    {
        this->alignment = a;
        setText(text);
    }


} // fruitwork