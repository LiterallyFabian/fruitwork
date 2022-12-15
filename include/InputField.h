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
            /** Allows any character to be entered. */
            TEXT,
            /** Allows only integers to be entered. */
            NUMERIC,
            /** Allows any character to be entered, but the input is hidden. */
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

        void setMaxLength(int ml);

        int getMaxLength() const { return maxLength; }

    protected:
        InputField(int x, int y, int w, int h, const std::string &placeholderText, InputType inputType);

    private:
#pragma region Input field properties

        /** The currently entered text. */
        std::string text;

        /** The maximum allowed amount of characters. */
        int maxLength = 20;

        InputType inputType = TEXT;

        /** The placeholder text to show when the input field is empty. */
        std::string placeholderText;

        /** If the input field is currently focused it should show the caret. */
        bool isFocused = false;

        /** If the input field is currently hovered it should be slightly gray. */
        bool isHovered = false;

        SDL_Texture *textTexture = nullptr;
        SDL_Texture *placeholderTexture = nullptr;
        SDL_Texture *textureLeft, *textureMiddle, *textureRight;

        /** The amount of input fields currently listening for input. */
        static int listenerCount;

        /** Stop or start accepting input. */
        static void setListenerState(bool listening);

        /** Replaces all characters with an asterisk. */
        std::string getPasswordMask() const;

#pragma endregion

#pragma region Caret properties

        /**
         * How many frames the caret should be visible for.
         * This is 0.53 seconds, which is the same as the default blink rate of the Windows caret.
         * @see https://superuser.com/a/815369/1536955
         */
        const int CARET_BLINK_INTERVAL = (double) constants::gFps / 1.88; // NOLINT
        int caretBlinkCounter = 0;
        bool caretVisible = true;
        SDL_Texture *caretTexture = nullptr;
        int caretPosition = 0;

#pragma endregion
    };

} // fruitwork

#endif //FRUITWORK_INPUTFIELD_H
