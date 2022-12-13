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
        SDL_RenderCopy(sys.getRenderer(), texture, nullptr, &drawRect);
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

        if (isFontOwner)
        {
            TTF_CloseFont(font);
            font = TTF_OpenFont(fontPath.c_str(), fontSize);
        }

        SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);
        SDL_FreeSurface(surface);

        // set the draw rect
        drawRect = getRect();
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
                drawRect.x += (getRect().w - w) / 2;
                break;
            case Alignment::RIGHT:
                drawRect.w = w;
                drawRect.h = h;
                drawRect.x += getRect().w - w;
                break;
        }

        // drawRect can not be larger than the component's rect, scale x and y down by the same % if necessary
        if (drawRect.w > getRect().w)
        {
            float scale = (float) getRect().w / drawRect.w;
            drawRect.w *= scale;
            drawRect.h *= scale;
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

    void Label::setFontPath(const std::string &f)
    {
        this->fontPath = f;
        this->isFontOwner = true;
        setText(text);
    }

    void Label::setFont(TTF_Font *f)
    {
        if (this->isFontOwner)
            TTF_CloseFont(this->font);

        this->font = f;
        this->isFontOwner = false;
        setText(text);
    }

    void Label::setAlignment(Label::Alignment a)
    {
        this->alignment = a;
        setText(text);
    }


} // fruitwork