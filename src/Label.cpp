#include "Label.h"
#include "System.h"
#include <SDL_ttf.h>
#include <iostream>

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
        SDL_RenderCopy(sys.get_renderer(), texture, nullptr, &get_rect());
    }

    Label::~Label()
    {
        SDL_DestroyTexture(texture);
    }

    std::string Label::getText() const { return text; }

    void Label::setText(const std::string &t)
    {
        text = t;
        try
        {
            SDL_DestroyTexture(texture);
        }
        catch (std::exception &e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        SDL_Surface *surface = TTF_RenderText_Solid(sys.get_font(), text.c_str(), color);
        if (surface == nullptr)
        {
            SDL_Log("TTF_RenderText_Solid: %s", TTF_GetError());
            return;
        }

        texture = SDL_CreateTextureFromSurface(sys.get_renderer(), surface);

        SDL_FreeSurface(surface);
    }

    void Label::setColor(const SDL_Color &c)
    {
        this->color = c;
        setText(text);
    }


} // fruitwork