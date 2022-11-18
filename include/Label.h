#ifndef FRUITWORK_LABEL_H
#define FRUITWORK_LABEL_H

#include <string>
#include "Component.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "System.h"

namespace fruitwork
{

    class Label : public Component {

    public:
        enum class Alignment {
            LEFT,
            CENTER,
            RIGHT
        };

        static Label *getInstance(int x, int y, int w, int h, const std::string &text);

        std::string getText() const;

        void setText(const std::string &text);

        void setColor(const SDL_Color &color);

        void setFontSize(int size);

        void setFont(const std::string &f);

        void setAlignment(Alignment a);

        void draw() const override;

        ~Label() override;

    protected:
        Label(int x, int y, int w, int h, const std::string &text);

    private:
        std::string text;
        SDL_Texture *texture = nullptr;
        SDL_Color color = {0, 0, 0, 255};

        int fontSize = 24;
        std::string fontName = "KGRedHands.ttf";
        TTF_Font *font = nullptr;
        Alignment alignment = Alignment::LEFT;

        /**
         * The rect that the text is drawn to.
         */
        SDL_Rect drawRect;
    };

} // fruitwork

#endif //FRUITWORK_LABEL_H
