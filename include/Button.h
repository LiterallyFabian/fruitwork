#ifndef FRUITWORK_BUTTON_H
#define FRUITWORK_BUTTON_H

#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Component.h"

namespace fruitwork
{

    class Button : public Component {

    public:
        enum class State {
            /**
             * The button is not being hovered over.
             */
            NORMAL,

            /**
             * The button is being hovered over.
             */
            HOVER,

            /**
             * The button is being clicked.
             */
            PRESSED
        };

        static Button *getInstance(int x, int y, int w, int h, std::string text);

        void onMouseDown(const SDL_Event &) override;

        void onMouseUp(const SDL_Event &) override;

        void draw() const override;

        void update() override;

        void setTextColor(const SDL_Color &color);

        void setColor(const SDL_Color &color);

        /**
         * Register a callback function to be called when the button is clicked.
         * @param callback The callback function.
         */
        void registerCallback(void (*callback)(Button *source));

        std::string getText() const { return text; }

        ~Button() override;

    protected:
        Button(int x, int y, int w, int h, std::string text);

        State state = State::NORMAL;
        bool isDown = false;

        SDL_Color buttonColor = {255, 255, 255, 255};
        Mix_Chunk *clickSound, *hoverSound;

        void (*onClick)(Button *source) = nullptr;

        void setState(State state);

    private:
        std::string text;
        SDL_Texture *textTexture;
        SDL_Texture *buttonTextureLeft, *buttonTextureMiddle, *buttonTextureRight;
        SDL_Color textColor = {0, 0, 0, 255};

        static TTF_Font *font;
    };

} // fruitwork

#endif //FRUITWORK_BUTTON_H
