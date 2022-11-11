#ifndef FRUITWORK_LABEL_H
#define FRUITWORK_LABEL_H

#include <string>
#include "Component.h"
#include <SDL.h>

namespace fruitwork
{

    class Label : public Component {

    public:
        static Label *getInstance(int x, int y, int w, int h, const std::string &text);

        std::string getText() const;

        void setText(const std::string &text);

        void draw() const override;

        ~Label() override;


    protected:
        Label(int x, int y, int w, int h, const std::string &text);

    private:
        std::string text;
        SDL_Texture *texture;
    };

} // fruitwork

#endif //FRUITWORK_LABEL_H
