#ifndef FRUITWORK_INPUTFIELD_H
#define FRUITWORK_INPUTFIELD_H

#include <string>
#include <SDL_ttf.h>
#include "Component.h"
#include "Constants.h"

namespace fruitwork
{

    class InputField : public Component {
    public:
        enum InputType {
            /**
             * Allows any character to be entered.
             */
            TEXT,
            /**
             * Allows only integers to be entered.
             */
            NUMERIC,
            /**
             * Allows any character to be entered, but the input is hidden.
             */
            PASSWORD
        };

        static InputField *getInstance(int x, int y, int w, int h, const std::string &placeholderText, InputType inputType = TEXT);

        void draw() const override;

        ~InputField() override;

        void update() override;

        void onMouseDown(const SDL_Event &) override;

        void onTextInput(const SDL_Event &) override;

        void onKeyDown(const SDL_Event &) override;

        void setText(const std::string &t);

        const std::string &getText() const { return text; }

        void setMaxLength(int ml) { this->maxLength = ml; }

        int getMaxLength() const { return maxLength; }

    protected:
        InputField(int x, int y, int w, int h, const std::string &placeholderText, InputType inputType);

    private:
        std::string text;
        int maxLength = 20;

        InputType inputType = TEXT;
        std::string placeholderText;

        bool isFocused = false;
        bool isHovered = false;

        /**
         * How many frames the caret should be visible for.
         * This is 0.53 seconds, which is the same as the default blink rate of the Windows caret.
         * @see https://superuser.com/a/815369/1536955
         */
        const int caretBlinkInterval = (double) constants::gFps / 1.88; // NOLINT
        int caretBlinkCounter = 0;
        bool caretVisible = true;

        SDL_Texture *placeholderTexture = nullptr;
        SDL_Texture *textureLeft, *textureMiddle, *textureRight;
        SDL_Texture *caretTexture = nullptr;
        SDL_Texture *textTexture = nullptr;
        SDL_Rect caretRect = {0, 0, 0, 0};
    };

} // fruitwork

#endif //FRUITWORK_INPUTFIELD_H
