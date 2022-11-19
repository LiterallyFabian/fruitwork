#include <iostream>
#include <SDL_image.h>
#include "InputField.h"
#include "ResourceManager.h"
#include "System.h"

namespace fruitwork
{
    InputField *InputField::getInstance(int x, int y, int w, int h, InputType inputType)
    {
        return new InputField(x, y, w, h, inputType);
    }

    InputField::InputField(int x, int y, int w, int h, InputType inputType)
            : Component(x, y, w, h), inputType(inputType)
    {
        textureLeft = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button-left.png").c_str());
        textureMiddle = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button-middle.png").c_str());
        textureRight = IMG_LoadTexture(fruitwork::sys.get_renderer(), ResourceManager::getTexturePath("button-right.png").c_str());

        // 1x1 white pixel
        caretTexture = SDL_CreateTexture(fruitwork::sys.get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1, 1);
    }

    void InputField::draw() const
    {
        SDL_Rect rect = get_rect();

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
        SDL_Rect textRect = {rect.x + 10, rect.y + 10, rect.w - 20, rect.h - 20};
        int w, h;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &w, &h);
        textRect.w = w;
        textRect.h = h;
        SDL_RenderCopy(fruitwork::sys.get_renderer(), textTexture, nullptr, &textRect);

        // draw caret
        if (caretVisible && isFocused)
        {
            SDL_SetRenderTarget(fruitwork::sys.get_renderer(), caretTexture);
            SDL_SetRenderDrawColor(fruitwork::sys.get_renderer(), 0, 0, 0, 255);
            SDL_RenderClear(fruitwork::sys.get_renderer());
            SDL_SetRenderTarget(fruitwork::sys.get_renderer(), nullptr);

            SDL_Rect caretRect = {rect.x + 10 + w, rect.y + 10, 2, rect.h - 20};
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

            SDL_Log("InputField::onMouseDown: isFocused = true");
        }
        else if (!inRect && isFocused)
        {
            isFocused = false;
            SDL_StopTextInput();

            SDL_Log("InputField::onMouseDown: isFocused = false");
        }
    }

    void InputField::onTextInput(const SDL_Event &event)
    {
        if (isFocused)
        {
            if (maxLength > 0 && text.length() >= maxLength)
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
            case SDLK_LEFT:
                if (caretPosition > 0)
                    caretPosition--;
                break;
            case SDLK_RIGHT:
                if (caretPosition < text.length())
                    caretPosition++;
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
            for (int i = 0; i < t.length(); i++)
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
    }

} // fruitwork