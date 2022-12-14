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
        textureLeft = IMG_LoadTexture(fruitwork::sys.getRenderer(), ResourceManager::getTexturePath("button-left.png").c_str());
        textureMiddle = IMG_LoadTexture(fruitwork::sys.getRenderer(), ResourceManager::getTexturePath("button-middle.png").c_str());
        textureRight = IMG_LoadTexture(fruitwork::sys.getRenderer(), ResourceManager::getTexturePath("button-right.png").c_str());

        // 1x1 pixel to stretch
        caretTexture = SDL_CreateTexture(fruitwork::sys.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1, 1);

        SDL_Surface *placeholderSurface = TTF_RenderText_Blended(sys.getFont(), placeholderText.c_str(), {0, 0, 0, 128});
        placeholderTexture = SDL_CreateTextureFromSurface(fruitwork::sys.getRenderer(), placeholderSurface);
        SDL_FreeSurface(placeholderSurface);
    }

    void InputField::draw() const
    {
        SDL_Rect rect = getRect();
        bool usePlaceholder = text.empty();

        SDL_Rect leftRect = {rect.x, rect.y, 8, rect.h};
        SDL_Rect middleRect = {rect.x + 8, rect.y, rect.w - 16, rect.h};
        SDL_Rect rightRect = {rect.x + rect.w - 8, rect.y, 8, rect.h};

        const int color = isFocused ? 240 : 255;
        SDL_SetTextureColorMod(textureLeft, color, color, color);
        SDL_SetTextureColorMod(textureMiddle, color, color, color);
        SDL_SetTextureColorMod(textureRight, color, color, color);

        SDL_RenderCopy(fruitwork::sys.getRenderer(), textureLeft, nullptr, &leftRect);
        SDL_RenderCopy(fruitwork::sys.getRenderer(), textureMiddle, nullptr, &middleRect);
        SDL_RenderCopy(fruitwork::sys.getRenderer(), textureRight, nullptr, &rightRect);

        // draw text with padding
        SDL_Texture *texture = usePlaceholder ? placeholderTexture : textTexture;
        SDL_Rect textRect = {rect.x + 10, rect.y + 10, rect.w - 20, rect.h - 20};
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        textRect.w = w;
        textRect.h = h;
        SDL_RenderCopy(fruitwork::sys.getRenderer(), texture, nullptr, &textRect);

        // draw caret
        if (caretVisible && isFocused)
        {
            SDL_SetRenderDrawColor(fruitwork::sys.getRenderer(), 0, 0, 0, 255);

            SDL_Rect caretRect = {rect.x + 10, rect.y + 10, 2, rect.h - 20};

            if (caretPosition > 0)
            {
                SDL_Surface *tmpSurface = TTF_RenderText_Blended(sys.getFont(), text.substr(0, caretPosition).c_str(), {0, 0, 0, 255});
                SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(fruitwork::sys.getRenderer(), tmpSurface);
                SDL_FreeSurface(tmpSurface);

                SDL_QueryTexture(tmpTexture, nullptr, nullptr, &caretRect.x, nullptr);
                SDL_DestroyTexture(tmpTexture);

                caretRect.x += rect.x + 10;
            }

            SDL_RenderCopy(fruitwork::sys.getRenderer(), caretTexture, nullptr, &caretRect);
        }
    }

    void InputField::update()
    {
        // update caret
        caretBlinkCounter++;
        if (caretBlinkCounter > CARET_BLINK_INTERVAL)
        {
            caretBlinkCounter = 0;
            caretVisible = !caretVisible;
        }

        // update cursor
        SDL_Point mousePos = {0, 0};
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        if (SDL_PointInRect(&mousePos, &getRect()))
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
        bool inRect = SDL_PointInRect(&mousePos, &getRect());

        if (inRect && !isFocused)
        {
            isFocused = true;
            setListenerState(true);
            caretPosition = text.length();
        }
        else if (!inRect && isFocused)
        {
            isFocused = false;
            setListenerState(false);
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

            text.insert(caretPosition, event.text.text);
            setText(text);

            caretBlinkCounter = 0;
            caretVisible = true; // the caret is always visible when typing
            caretPosition += strlen(event.text.text);
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
                    text.erase(caretPosition - 1, 1);
                    setText(text); // update texture

                    caretBlinkCounter = 0;
                    caretVisible = true; // the caret is always visible when typing
                    caretPosition--;
                }
                break;

            case SDLK_DELETE:
                if (text.length() > 0)
                {
                    text.erase(caretPosition, 1);
                    setText(text); // update texture

                    caretBlinkCounter = 0;
                    caretVisible = true; // the caret is always visible when typing
                }
                break;

            case SDLK_RETURN:
            case SDLK_ESCAPE:
                setListenerState(false);
                isFocused = false;
                break;

            case SDLK_LEFT:
                caretPosition = std::max(0, caretPosition - 1);
                caretBlinkCounter = 0;
                caretVisible = true;
                break;
            case SDLK_RIGHT:
                caretPosition = std::min(int(text.length()), caretPosition + 1);
                caretBlinkCounter = 0;
                caretVisible = true;
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
        SDL_Surface *surface = TTF_RenderText_Blended(sys.getFont(), shownText.c_str(), {0, 0, 0});
        textTexture = SDL_CreateTextureFromSurface(fruitwork::sys.getRenderer(), surface);
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

    int InputField::listenerCount = 0;

    void InputField::setListenerState(bool listening)
    {
        if (listening)
        {
            listenerCount++;
            SDL_StartTextInput();
        }
        else
        {
            listenerCount--;
            if (listenerCount == 0)
                SDL_StopTextInput();
        }
    }

    void InputField::setMaxLength(int ml)
    {
        this->maxLength = ml;
        if (maxLength > 0 && int(text.length()) > maxLength)
        {
            setText(text.substr(0, maxLength));
        }
    }

} // fruitwork