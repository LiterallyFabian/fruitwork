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
        static InputField *getInstance(int x, int y, int w, int h);

        void draw() const override;

        ~InputField() override;

        void update() override;

        void onMouseDown(const SDL_Event &) override;

        void onTextInput(const SDL_Event &) override;

        void onTextEditing(const SDL_Event &) override;

        void onKeyDown(const SDL_Event &) override;

        void setText(const std::string &t);

        const std::string &getText() const { return text; }

        void setMaxLength(int ml) { this->maxLength = ml; }

        int getMaxLength() const { return maxLength; }

    protected:
        InputField(int x, int y, int w, int h);

    private:
        std::string text = "";

        int maxLength = 20;
        bool isFocused = false;

        /**
         * How many frames the caret should be visible for.
         * This is 0.53 seconds, which is the same as the default blink rate of the Windows caret.
         * @see https://superuser.com/a/815369/1536955
         */
        const int caretBlinkInterval = (double) constants::gFps / 1.88; // NOLINT
        int caretPosition = 0;
        int caretBlinkCounter = 0;
        bool caretVisible = true;

        SDL_Texture *textureLeft, *textureMiddle, *textureRight;
        SDL_Texture *caretTexture = nullptr;
        SDL_Texture *textTexture = nullptr;
        SDL_Rect caretRect = {0, 0, 0, 0};
    };

} // fruitwork

#endif //FRUITWORK_INPUTFIELD_H
