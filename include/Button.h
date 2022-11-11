#ifndef FRUITWORK_BUTTON_H
#define FRUITWORK_BUTTON_H

#include <string>
#include <SDL.h>
#include "Component.h"

namespace fruitwork
{

    class Button : public Component {

    public:
        static Button *getInstance(int x, int y, int w, int h, std::string text);

        void onMouseDown(const SDL_Event &) override;

        void onMouseUp(const SDL_Event &) override;

        void draw() const override;

        /**
         * Register a callback function to be called when the button is clicked.
         * @param callback The callback function.
         */
        void registerCallback(void (*callback)(Button *source));

        std::string getText() const;

        ~Button() override;

    protected:
        Button(int x, int y, int w, int h, std::string text);

    private:
        std::string text;
        SDL_Texture *textTexture;
        SDL_Texture *buttonTexture, *buttonTextureDown;
        bool isDown = false;

        void (*onClick)(Button *source);
    };

} // fruitwork

#endif //FRUITWORK_BUTTON_H
