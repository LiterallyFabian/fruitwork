#include <iostream>
#include <SDL_image.h>
#include "InputField.h"
#include "ResourceManager.h"
#include "System.h"

namespace fruitwork
{
    InputField *InputField::getInstance(int x, int y, int w, int h, const std::string &placeholderText, InputType inputType)
    {
        return new InputField(x, y, w, h, placeholderText, inputType);
    }

    InputField::InputField(int x, int y, int w, int h, const std::string &placeholderText, InputType inputType)
            : Component(x, y, w, h), inputType(inputType), placeholderText(placeholderText)
    {
        textureLeft = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button-left.png").c_str());
        textureMiddle = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button-middle.png").c_str());
        textureRight = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button-right.png").c_str());

        // 1x1 white pixel
        caretTexture = SDL_CreateTexture(fruitwork::sys.get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1, 1);

        SDL_Surface *placeholderSurface = TTF_RenderText_Blended(sys.get_font(), placeholderText.c_str(), {0, 0, 0, 128});
        placeholderTexture = SDL_CreateTextureFromSurface(fruitwork::sys.get_renderer(), placeholderSurface);
        SDL_FreeSurface(placeholderSurface);
    }

    void InputField::draw() const
    {
        SDL_Rect rect = get_rect();
        bool usePlaceholder = text.empty();

        SDL_Rect leftRect = {rect.x, rect.y, 8, rect.h};
        SDL_Rect middleRect = {rect.x + 8, rect.y, rect.w - 16, rect.h};
        SDL_Rect rightRect = {rect.x + rect.w - 8, rect.y, 8, rect.h};

        const int color = isFocused ? 240 : 255;
        SDL_SetTextureColorMod(textureLeft, color, color, color);
        SDL_SetTextureColorMod(textureMiddle, color, color, color);
        SDL_SetTextureColorMod(textureRight, color, color, color);

        SDL_RenderCopy(fruitwork::sys.get_renderer(), textureLeft, nullptr, &leftRect);
        SDL_RenderCopy(fruitwork::sys.get_renderer(), textureMiddle, nullptr, &middleRect);
        SDL_RenderCopy(fruitwork::sys.get_renderer(), textureRight, nullptr, &rightRect);

        // draw text with padding
        SDL_Texture *texture = usePlaceholder ? placeholderTexture : textTexture;
        SDL_Rect textRect = {rect.x + 10, rect.y + 10, rect.w - 20, rect.h - 20};
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        textRect.w = w;
        textRect.h = h;
        SDL_RenderCopy(fruitwork::sys.get_renderer(), texture, nullptr, &textRect);

        // draw caret
        if (caretVisible && isFocused)
        {
            SDL_SetRenderTarget(fruitwork::sys.get_renderer(), caretTexture);
            SDL_SetRenderDrawColor(fruitwork::sys.get_renderer(), 0, 0, 0, 255);
            SDL_RenderClear(fruitwork::sys.get_renderer());
            SDL_SetRenderTarget(fruitwork::sys.get_renderer(), nullptr);

            SDL_Rect caretRect = {rect.x + 10 + w, rect.y + 10, 2, rect.h - 20};

            // move back caret if placeholder is shown
            if (usePlaceholder)
                caretRect.x = rect.x + 10;

            SDL_RenderCopy(fruitwork::sys.get_renderer(), caretTexture, nullptr, &caretRect);
        }
    }

    void InputField::update()
    {
        // update caret
        caretBlinkCounter++;
        if (caretBlinkCounter > caretBlinkInterval)
        {
            caretBlinkCounter = 0;
            caretVisible = !caretVisible;
        }

        // update cursor
        SDL_Point mousePos = {0, 0};
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        if (SDL_PointInRect(&mousePos, &get_rect()))
        {
            isHovered = true;
            SDL_SetCursor(sys.getCursorText());
        }
        else if (isHovered)
        {
            isHovered = false;
            SDL_SetCursor(sys.getCursorDefault());
        }
    }

    void InputField::onMouseDown(const SDL_Event &)
    {
        SDL_Point mousePos;
        SDL_GetMouseState(&mousePos.x, &mousePos.y);
        bool inRect = SDL_PointInRect(&mousePos, &get_rect());

        if (inRect && !isFocused)
        {
            isFocused = true;
            SDL_StartTextInput();
        }
        else if (!inRect && isFocused)
        {
            isFocused = false;
            SDL_StopTextInput();
        }
    }

    void InputField::onTextInput(const SDL_Event &event)
    {
        if (isFocused)
        {
            if (maxLength > 0 && int(text.length()) >= maxLength)
                return;

            if (inputType == InputType::NUMERIC)
            {
                if (event.text.text[0] < '0' || event.text.text[0] > '9')
                    return;
            }

            text += event.text.text;
            setText(text); // update text texture

            caretBlinkCounter = 0;
            caretVisible = true; // the caret is always visible when typing
        }
    }

    void InputField::onKeyDown(const SDL_Event &event)
    {
        if (!isFocused)
            return;

        switch (event.key.keysym.sym)
        {
            case SDLK_BACKSPACE:
                if (text.length() > 0)
                {
                    text.pop_back();
                    setText(text); // update texture
                }
                break;
            case SDLK_RETURN:
                SDL_StopTextInput();
                isFocused = false;
                break;
            default:
                break;
        }
    }

    void InputField::setText(const std::string &t)
    {
        this->text = t;
        std::string shownText = t;

        // replace all symbols with asterisks
        if (inputType == InputType::PASSWORD)
        {
            // @see https://stackoverflow.com/a/39082873/11420970
            for (std::string::size_type i = 0; i < t.length(); i++)
                shownText[i] = '*';
        }

        SDL_DestroyTexture(textTexture);
        SDL_Surface *surface = TTF_RenderText_Blended(sys.get_font(), shownText.c_str(), {0, 0, 0});
        textTexture = SDL_CreateTextureFromSurface(fruitwork::sys.get_renderer(), surface);
        SDL_FreeSurface(surface);
    }

    InputField::~InputField()
    {
        SDL_DestroyTexture(textureLeft);
        SDL_DestroyTexture(textureMiddle);
        SDL_DestroyTexture(textureRight);
        SDL_DestroyTexture(caretTexture);
        SDL_DestroyTexture(textTexture);
        SDL_DestroyTexture(placeholderTexture);
    }

} // fruitwork