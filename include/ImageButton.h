#ifndef FRUITWORK_IMAGEBUTTON_H
#define FRUITWORK_IMAGEBUTTON_H

#include "Button.h"
#include "Sprite.h"
#include "ResponsiveSprite.h"

namespace fruitwork
{

    class ImageButton : public Button {
    public:
        static ImageButton *getInstance(int x, int y, int w, int h, SDL_Texture *texture);

        static ImageButton *getInstance(int x, int y, int w, int h, const std::string &texturePath);

        void setFlip(SDL_RendererFlip flip) { this->flipType = flip; }

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

        SDL_RendererFlip flipType = SDL_FLIP_NONE;
    };

} // fruitwork

#endif //FRUITWORK_IMAGEBUTTON_H
