#ifndef FRUITWORK_IMAGE_BUTTON_H
#define FRUITWORK_IMAGE_BUTTON_H

#include "Button.h"
#include "Sprite.h"
#include "ResponsiveSprite.h"

namespace fruitwork
{

    class ImageButton : public Button {
    public:
        static ImageButton *getInstance(int x, int y, int w, int h, SDL_Texture *texture);

        static ImageButton *getInstance(int x, int y, int w, int h, const std::string &texturePath);

        void start() override;

        void draw() const override;

        ~ImageButton() override;

    protected:
        ImageButton(int x, int y, int w, int h, SDL_Texture *texture);

        ImageButton(int x, int y, int w, int h, const std::string &texturePath);

    private:
        SDL_Rect originalRect;
        ResponsiveSprite *sprite;
        bool isSpriteOwner = true;
    };

} // fruitwork

#endif //FRUITWORK_IMAGE_BUTTON_H
