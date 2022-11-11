#include "Label.h"
#include "System.h"
#include <SDL_ttf.h>

namespace fruitwork
{
    Label *Label::getInstance(int x, int y, int w, int h, const std::string &text)
    {
           return new Label(x, y, w, h, text);
    }

    Label::Label(int x, int y, int w, int h,
                            const std::string &text) : Component(x, y, w, h), text(text)
    {
        static const SDL_Color color = {0, 0, 0, 255}; // black
        SDL_Surface *surface = TTF_RenderText_Solid(sys.get_font(), text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(sys.get_renderer(), surface);
        SDL_FreeSurface(surface);
    }

    void Label::draw() const
    {
        SDL_RenderCopy(sys.get_renderer(), texture, nullptr, &get_rect());
    }

    Label::~Label()
    {
        SDL_DestroyTexture(texture);
    }

} // fruitwork