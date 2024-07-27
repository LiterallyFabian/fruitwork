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

    void Label::update()
    {
        Component::update();
        SDL_Rect currentRect = getAbsoluteRect();
        if (!SDL_RectEquals(&currentRect, &lastAbsoluteDrawnRect))
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

        drawRect = getAbsoluteRect();

        SDL_Surface *surface;
        if (allowWrap)
            surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, drawRect.w * 1.1);
        else
            surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);

        texture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);
        SDL_FreeSurface(surface);

        // set the draw rect
        int textWidth, textHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

        // drawRect can not be larger than the component's rect, scale x and y down by the same % if necessary
        if (textWidth > drawRect.w)
        {
            float scale = static_cast<float>(drawRect.w) / textWidth;
            textWidth = static_cast<int>(textWidth * scale);
            textHeight = static_cast<int>(textHeight * scale);
        }

        drawRect.w = textWidth;
        drawRect.h = textHeight;

        switch (alignment)
        {
            case Alignment::LEFT:
                break;
            case Alignment::CENTER:
                drawRect.x += (getAbsoluteRect().w - textWidth) / 2; // Full width minus text width divided by 2
                break;
            case Alignment::RIGHT:
                drawRect.x += getAbsoluteRect().w - textWidth; // Full width minus text width
                break;
        }

        lastAbsoluteDrawnRect = getAbsoluteRect();
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